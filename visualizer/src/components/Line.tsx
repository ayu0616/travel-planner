import { ComponentProps } from 'react'

export interface LineProps extends ComponentProps<'line'> {}

export const Line = ({ ...props }: LineProps) => {
    return <line {...props} />
}
