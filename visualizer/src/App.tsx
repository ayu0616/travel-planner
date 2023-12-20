import { useState } from 'react'

import { Circle, Line, Svg } from './components'

interface Spot {
    arriveAfter: number
    arriveBefore: number
    latitude: number
    longitude: number
    priority: number
    stayTime: number
}

interface Grid {
    x: number
    y: number
}

interface Edge {
    from: number
    to: number
}

const r = 10
const maxHeight = 600
const maxWidth = 600

const convert = (spots: Spot[]): Grid[] => {
    const minX = Math.min(...spots.map(({ longitude: x }) => x))
    const minY = Math.min(...spots.map(({ latitude: y }) => y))
    const maxX = Math.max(...spots.map(({ longitude: x }) => x))
    const maxY = Math.max(...spots.map(({ latitude: y }) => y))
    const width = maxX - minX
    const height = maxY - minY
    const maxH = maxHeight - 2 * r
    const maxW = maxWidth - 2 * r
    const newSpots = spots.map(({ longitude: x, latitude: y }) => {
        return {
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
    const lines = inText.split('\n')
    const spots: Spot[] = []
    for (const line of lines) {
        if (line === '') continue
        const [
            arriveBefore,
            arriveAfter,
            stayTime,
            priority,
            latitude,
            longitude,
        ] = line.split(' ').map((s) => Number(s))
        spots.push({
            arriveAfter,
            arriveBefore,
            latitude,
            longitude,
            priority,
            stayTime,
        })
    }
    return spots
}

const outToPaths = (outText: string): number[][] => {
    const lines = outText.split('\n')
    const paths: number[][] = []
    for (const line of lines) {
        if (line === '') continue
        const path = line.split(' ').map((s) => Number(s))
        paths.push(path)
    }
    return paths
}

function App() {
    const [inText, setInText] = useState('-1 28800 1800 3 1 1')
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
                    <div>
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
                        <span>{pathIndex}</span>
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
                        {newSpots.map(({ x, y }, i) => {
                            return (
                                <Circle
                                    key={i}
                                    cx={x}
                                    cy={y}
                                    fill='pink'
                                    label={i.toString()}
                                    r={r}
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
