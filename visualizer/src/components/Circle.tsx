import { ComponentProps } from 'react'

export interface CircleProps extends ComponentProps<'circle'> {
    label?: string
    textClass?: string
}

export const Circle = ({ r = 20, label, textClass, ...props }: CircleProps) => {
    return (
        <>
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
        </>
    )
}
