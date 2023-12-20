import { ComponentProps } from 'react'

export interface CircleProps extends ComponentProps<'circle'> {
    label?: string
}

export const Circle = ({ r = 20, label, ...props }: CircleProps) => {
    return (
        <>
            <circle r={r} {...props} />
            {label && (
                <text
                    dominant-baseline='central'
                    text-anchor='middle'
                    x={props.cx}
                    y={props.cy}
                >
                    {label}
                </text>
            )}
        </>
    )
}
