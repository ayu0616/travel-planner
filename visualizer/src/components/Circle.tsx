import { ComponentProps, useState } from 'react'

export interface CircleProps extends ComponentProps<'circle'> {
    label?: string
    selected?: boolean
    textClass?: string
}

export const Circle = ({
    r = 20,
    label,
    textClass,
    selected = false,
    ...props
}: CircleProps) => {
    const [isHovered, setIsHovered] = useState(false)

    return (
        <g
            className='select-none'
            onMouseEnter={() => setIsHovered(true)}
            onMouseLeave={() => setIsHovered(false)}
        >
            {selected && (
                <circle
                    r={Number(r) * 1.15}
                    {...props}
                    className='fill-red-400'
                />
            )}
            <circle r={r} {...props} />
            {label && (
                <text
                    className={[selected ? 'font-bold' : '', textClass].join(
                        ' ',
                    )}
                    dominant-baseline='central'
                    text-anchor='middle'
                    x={props.cx}
                    y={props.cy}
                >
                    {label}
                </text>
            )}
            {isHovered && (
                <circle r={r} {...props} className='fill-white opacity-50' />
            )}
        </g>
    )
}
