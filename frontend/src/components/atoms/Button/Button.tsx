import { arrToClass } from '../../../util'

interface ButtonProps
    extends React.DetailedHTMLProps<
        React.ButtonHTMLAttributes<HTMLButtonElement>,
        HTMLButtonElement
    > {
    /** 見た目の種類 */
    variant?: 'normal' | 'outline'
}

const variantToClass = (variant: ButtonProps['variant']) => {
    switch (variant) {
        case 'normal':
            return 'bg-green-700 text-white hover:bg-green-800 active:bg-green-900'
        case 'outline':
            return 'bg-transparent text-green-700 outline outline-2 -outline-offset-2 outline-green-700 hover:bg-green-800 hover:text-white hover:outline-green-800 active:bg-green-900 active:text-white'
        default:
            return ''
    }
}

const Button = ({
    variant = 'normal',
    className = '',
    ...props
}: ButtonProps) => {
    const variantClass = variantToClass(variant)
    return (
        <button
            className={arrToClass(
                'rounded-md px-3 py-2 focus:ring-2 focus:ring-green-800/50',
                variantClass,
                className,
            )}
            {...props}
        ></button>
    )
}

export default Button
