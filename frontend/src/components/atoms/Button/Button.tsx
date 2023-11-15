import { arrToClass } from '../../../util';

interface ButtonProps extends React.DetailedHTMLProps<React.ButtonHTMLAttributes<HTMLButtonElement>, HTMLButtonElement>
 {
 }

const Button = ({className='', ...props }: ButtonProps) => {
  return <button className={arrToClass('text-white bg-green-700 py-2 px-3 rounded-md focus:outline outline-green-800/50 outline-2 hover:bg-green-800 active:bg-green-900',className)} {...props}></button>;
};

export default Button;
