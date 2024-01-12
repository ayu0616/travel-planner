import { useState } from 'react'

import { Circle, Line, Svg } from './components'

interface Spot {
    latitude: number
    longitude: number
    priority: number
}

interface Grid {
    priority: number
    x: number
    y: number
}

interface Edge {
    from: number
    to: number
}

const r = 12.5
const maxHeight = 800
const maxWidth = 800

const convert = (spots: Spot[]): Grid[] => {
    const minX = Math.min(...spots.map(({ longitude: x }) => x))
    const minY = Math.min(...spots.map(({ latitude: y }) => y))
    const maxX = Math.max(...spots.map(({ longitude: x }) => x))
    const maxY = Math.max(...spots.map(({ latitude: y }) => y))
    const width = maxX - minX
    const height = maxY - minY
    const maxH = maxHeight - 2 * r
    const maxW = maxWidth - 2 * r
    const newSpots = spots.map(({ longitude: x, latitude: y, priority }) => {
        return {
            priority,
            x: ((x - minX) / width) * maxW + r,
            y: ((maxY - y) / height) * maxH + r,
        }
    })
    return newSpots
}

const pathToEdges = (path: number[]): Edge[] => {
    const edges: Edge[] = []
    for (let i = 0; i < path.length - 1; i++) {
        edges.push({ from: path[i], to: path[i + 1] })
    }
    return edges
}

const inToSpots = (inText: string): Spot[] => {
    if (inText === '') return []
    const lines = inText.split('\n')
    const spots: Spot[] = []
    for (const line of lines) {
        if (line === '') continue
        const [latitude, longitude, priority] = line
            .split(' ')
            .map((s) => Number(s))
        spots.push({
            latitude,
            longitude,
            priority,
        })
    }
    return spots
}

const outToPaths = (outText: string): number[][] => {
    if (outText === '') return [[]]
    const lines = outText.split('\n')
    const paths: number[][] = []
    for (const line of lines) {
        if (line === '') continue
        const path = line.split(' ').map((s) => Number(s))
        paths.push(path)
    }
    return paths
}

const priorityToColor = (priority: number): string => {
    switch (priority) {
        case 1:
            return 'fill-green-200'
        case 2:
            return 'fill-yellow-200'
        case 3:
            return 'fill-red-200'
        case 100:
            return 'fill-red-800'
        default:
            return 'fill-gray-200'
    }
}

function App() {
    const [inText, setInText] = useState('1 1 3')
    const [outText, setOutText] = useState('0')
    const [pathIndex, setPathIndex] = useState(0)
    const spots = inToSpots(inText)
    const paths = outToPaths(outText)
    const path = paths[pathIndex]

    const newSpots = convert(spots)
    const edges = pathToEdges(path)

    return (
        <div className='bg-slate-50'>
            <div className='mx-auto flex max-w-[900px] flex-col items-center gap-4 p-8'>
                <div className='flex w-full flex-col gap-2 rounded-md border border-slate-200 bg-white p-4'>
                    <div className='flex flex-col gap-1'>
                        <label htmlFor='in'>入力</label>
                        <textarea
                            className='rounded-md border border-slate-200 p-2'
                            id='in'
                            value={inText}
                            onChange={(e) => setInText(e.target.value)}
                        ></textarea>
                    </div>
                    <div className='flex flex-col gap-1'>
                        <label htmlFor='out'>出力</label>
                        <textarea
                            className='rounded-md border border-slate-200 p-2'
                            id='out'
                            value={outText}
                            onChange={(e) => setOutText(e.target.value)}
                        ></textarea>
                    </div>
                    <div className='flex items-center gap-2'>
                        <label htmlFor='pathIndex'>ターン</label>
                        <input
                            id='pathIndex'
                            max={paths.length - 1}
                            min={0}
                            type='range'
                            value={pathIndex}
                            onChange={(e) =>
                                setPathIndex(Number(e.target.value))
                            }
                        />
                        {/* <span>{pathIndex}</span> */}
                        <input
                            className='rounded border border-slate-200 p-1'
                            max={paths.length - 1}
                            min={0}
                            type='number'
                            value={pathIndex}
                            onChange={(e) =>
                                setPathIndex(Number(e.target.value))
                            }
                        />
                    </div>
                </div>
                <div
                    className='max-w-full rounded-md border border-slate-200 bg-white p-4'
                    style={{ height: maxHeight, width: maxWidth }}
                >
                    <Svg maxHeight={maxHeight} maxWidth={maxWidth}>
                        {edges.map(({ from, to }, i) => {
                            const { x: x1, y: y1 } = newSpots[from]
                            const { x: x2, y: y2 } = newSpots[to]
                            return (
                                <Line
                                    key={i}
                                    stroke='black'
                                    strokeWidth={2}
                                    x1={x1}
                                    x2={x2}
                                    y1={y1}
                                    y2={y2}
                                />
                            )
                        })}
                        {newSpots.map(({ x, y, priority }, i) => {
                            return (
                                <Circle
                                    key={i}
                                    className={priorityToColor(priority)}
                                    cx={x}
                                    cy={y}
                                    label={i.toString()}
                                    r={r}
                                    textClass={
                                        priority === 100 ? 'fill-white' : ''
                                    }
                                />
                            )
                        })}
                    </Svg>
                </div>
            </div>
        </div>
    )
}

export default App
