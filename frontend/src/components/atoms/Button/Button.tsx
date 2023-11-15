import { arrToClass } from '../../../util'

interface ButtonProps
    extends React.DetailedHTMLProps<
        React.ButtonHTMLAttributes<HTMLButtonElement>,
        HTMLButtonElement
    > {}

const Button = ({ className = '', ...props }: ButtonProps) => {
    return (
        <button
            className={arrToClass(
                'rounded-md bg-green-700 px-3 py-2 text-white outline-2 outline-green-800/50 hover:bg-green-800 focus:outline active:bg-green-900',
                className,
            )}
            {...props}
        ></button>
    )
}

export default Button
