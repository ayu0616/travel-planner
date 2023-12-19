import { ComponentProps } from 'react'

export type SvgProps = Omit<ComponentProps<'svg'>, 'viewBox'> &
    (
        | {
              viewBox?: string
          }
        | {
              maxHeight?: number
              maxWidth?: number
          }
    )

export const Svg = ({
    xmlns = 'http://www.w3.org/2000/svg',
    ...props
}: SvgProps) => {
    const vb = (() => {
        if ('viewBox' in props && props.viewBox) return props.viewBox
        if (
            'maxHeight' in props &&
            'maxWidth' in props &&
            props.maxHeight &&
            props.maxWidth
        )
            return `0 0 ${props.maxWidth} ${props.maxHeight}`
        return undefined
    })()
    return <svg viewBox={vb} xmlns={xmlns} {...props} />
}
