import { arrToClass } from '../../../util';

export interface InputProps
  extends React.DetailedHTMLProps<
    React.InputHTMLAttributes<HTMLInputElement>,
    HTMLInputElement
  > {
  type?: 'text';
}

const Input = ({ type = 'text', className = '', ...props }: InputProps) => {
  return (
    <input
      className={arrToClass(
        'focus:outline outline-green-800/50 outline-2 rounded px-3 py-2 caret-green-700',
        className
      )}
      type={type}
      {...props}
    />
  );
};

export default Input;
