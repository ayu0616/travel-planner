interface LabelProps extends React.DetailedHTMLProps<React.LabelHTMLAttributes<HTMLLabelElement>, HTMLLabelElement> {}

const Label = ({ ...props }: LabelProps) => {
    return <label {...props}></label>;
};

export default Label;
