import { ComponentProps } from "react";

export interface CircleProps extends ComponentProps<"circle"> { }

export const Circle = ({r=20, ...props}: CircleProps) => {
    return <circle r={r} {...props} />;
}
