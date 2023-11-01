export interface InputProps extends React.DetailedHTMLProps<React.InputHTMLAttributes<HTMLInputElement>, HTMLInputElement> {
    type?: "text";
}

const Input = ({ type = "text", className = "", ...props }: InputProps) => {
    return <input type={type} className={["focus:outline outline-green-800/50 outline-2 rounded px-2 py-1", className].join(" ").trim()} {...props} />;
};

export default Input;
