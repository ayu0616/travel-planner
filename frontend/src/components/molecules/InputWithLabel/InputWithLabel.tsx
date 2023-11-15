import { ChangeEventHandler, useId } from "react";
import { Input } from "../../atoms/Input";
import { Label } from "../../atoms/Label";

interface InputWithLabelProps {
    id?: string;
    children?: string;
    value?: string;
    className?: string;
    onChange?: ChangeEventHandler<HTMLInputElement>;
}

const InputWithLabel = ({ id, children, className = "", ...props }: InputWithLabelProps) => {
    const useIdRes = useId();
    const _id = id ?? useIdRes;
    return (
        <div className={["flex items-center gap-4", className].join(" ").trim()}>
            <Label htmlFor={_id}>{children}</Label>
            <Input id={_id} {...props}></Input>
        </div>
    );
};

export default InputWithLabel;
