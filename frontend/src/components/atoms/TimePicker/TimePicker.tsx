import { DetailedHTMLProps, InputHTMLAttributes } from 'react'

import { arrToClass } from '../../../util'

interface TimePickerProps
    extends DetailedHTMLProps<
        InputHTMLAttributes<HTMLInputElement>,
        HTMLInputElement
    > {}

const TimePicker = ({
    type = 'time',
    className = '',
    ...props
}: TimePickerProps) => {
    return (
        <input
            className={arrToClass(
                'rounded p-2 caret-green-700 outline-2 outline-green-800/50 focus:outline',
                className,
            )}
            type='time'
            {...props}
        ></input>
    )
}

export default TimePicker
