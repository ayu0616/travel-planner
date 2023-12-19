import { useState } from 'react'

import { Circle, Line, Svg } from './components'

interface Spot {
    latitude: number
    longitude: number
}

interface Edge {
    from: number
    to: number
}

interface Data {
    path: number[]
    spots: Spot[]
}

const data: Data = {
    path: [0, 1, 2, 0],
    spots: [
        { latitude: 35, longitude: 135 },
        { latitude: 35.11, longitude: 136.123 },
        { latitude: 35.234, longitude: 135.798 },
        { latitude: 34.999, longitude: 135.555 },
    ],
}

const r = 10
const maxHeight = 600
const maxWidth = 600

const convert = (spots: Spot[]): Spot[] => {
    const minX = Math.min(...spots.map(({ longitude: x }) => x))
    const minY = Math.min(...spots.map(({ latitude: y }) => y))
    const maxX = Math.max(...spots.map(({ longitude: x }) => x))
    const maxY = Math.max(...spots.map(({ latitude: y }) => y))
    const width = maxX - minX
    const height = maxY - minY
    const maxH = maxHeight - 2 * r
    const maxW = maxWidth - 2 * r
    const newSpots: Spot[] = spots.map(({ longitude, latitude }) => {
        const newLongitude = ((longitude - minX) / width) * maxW + r
        const newLatitude = ((latitude - minY) / height) * maxH + r
        return { latitude: newLatitude, longitude: newLongitude }
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
        const [latitude, longitude] = line.split(' ').map((s) => Number(s))
        spots.push({ latitude, longitude })
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
    const [inText, setInText] = useState('1 1')
    const [outText, setOutText] = useState('0')
    const [pathIndex, setPathIndex] = useState(0)
    const spots = inToSpots(inText)
    const paths = outToPaths(outText)
    const path = paths[pathIndex]

    const newSpots = convert(spots)
    const edges = pathToEdges(path)

    return (
        <div
            style={{
                alignItems: 'center',
                display: 'flex',
                height: '100dvh',
                justifyContent: 'center',
                width: '100dvw',
            }}
        >
            <div style={{ height: maxHeight, width: maxWidth }}>
                <div>
                    <div>
                        <label htmlFor='in'>入力</label>
                        <textarea
                            id='in'
                            value={inText}
                            onChange={(e) => setInText(e.target.value)}
                        ></textarea>
                    </div>
                    <div>
                        <label htmlFor='out'>出力</label>
                        <textarea
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
                <Svg maxHeight={maxHeight} maxWidth={maxWidth}>
                    {edges.map(({ from, to }, i) => {
                        const { longitude: x1, latitude: y1 } = newSpots[from]
                        const { longitude: x2, latitude: y2 } = newSpots[to]
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
                    {newSpots.map(({ longitude: x, latitude: y }, i) => {
                        return <Circle key={i} cx={x} cy={y} fill='red' r={r} />
                    })}
                </Svg>
            </div>
        </div>
    )
}

export default App
