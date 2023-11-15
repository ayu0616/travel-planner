import { ChangeEventHandler, useId } from 'react';

import { arrToClass } from '../../../util';
import { Input } from '../../atoms/Input';
import { Label } from '../../atoms/Label';

interface InputWithLabelProps {
  children?: string;
  className?: string;
  id?: string;
  onChange?: ChangeEventHandler<HTMLInputElement>;
  value?: string;
}

const InputWithLabel = ({
  id,
  children,
  className = '',
  ...props
}: InputWithLabelProps) => {
  const useIdRes = useId();
  const _id = id ?? useIdRes;
  return (
    <div className={arrToClass('flex items-center gap-4', className)}>
      <Label htmlFor={_id}>{children}</Label>
      <Input id={_id} {...props}></Input>
    </div>
  );
};

export default InputWithLabel;
