import { ComponentProps } from 'react'

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
    return (
        <g>
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
                    className={textClass}
                    dominant-baseline='central'
                    text-anchor='middle'
                    x={props.cx}
                    y={props.cy}
                >
                    {label}
                </text>
            )}
        </g>
    )
}
