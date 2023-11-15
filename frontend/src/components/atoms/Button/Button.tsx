import { arrToClass } from '../../../util'

interface ButtonProps
    extends React.DetailedHTMLProps<
        React.ButtonHTMLAttributes<HTMLButtonElement>,
        HTMLButtonElement
    > {
    /** 見た目の種類 */
    variant?: 'normal' | 'outline' | 'secondary'
}

const variantToClass = (variant: ButtonProps['variant']) => {
    switch (variant) {
        case 'normal':
            return 'bg-emerald-700 text-white hover:bg-emerald-800 active:bg-emerald-900 focus:ring-emerald-800/50'
        case 'outline':
            return 'bg-transparent text-emerald-700 outline outline-2 -outline-offset-2 outline-emerald-700 hover:bg-emerald-800 hover:text-white hover:outline-emerald-800 active:bg-emerald-900 active:text-white focus:ring-emerald-800/50'
        case 'secondary':
            return 'bg-slate-500 text-white hover:bg-slate-500/80 active:bg-slate-500/50 focus:ring-slate-800/50'
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
                'rounded-md px-3 py-2 focus:ring-2',
                variantClass,
                className,
            )}
            {...props}
        ></button>
    )
}

export default Button
