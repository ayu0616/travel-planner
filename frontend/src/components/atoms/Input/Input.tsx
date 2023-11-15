import { arrToClass } from '../../../util'

export interface InputProps
    extends React.DetailedHTMLProps<
        React.InputHTMLAttributes<HTMLInputElement>,
        HTMLInputElement
    > {
    type?: 'text'
}

const Input = ({ type = 'text', className = '', ...props }: InputProps) => {
    return (
        <input
            className={arrToClass(
                'rounded px-3 py-2 caret-green-700 outline-2 outline-green-800/50 focus:outline',
                className,
            )}
            type={type}
            {...props}
        />
    )
}

export default Input
