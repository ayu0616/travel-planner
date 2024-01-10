import { ChangeEvent } from 'react'

import { TimePicker } from '../../atoms/TimePicker'

export interface TimeRange {
    from?: string
    to?: string
}

interface TimeRangePickerProps {
    onChange?: (value: TimeRange) => void
    value?: TimeRange
}

const TimeRangePicker = ({
    value = { from: undefined, to: undefined },
    onChange,
    ...props
}: TimeRangePickerProps) => {
    const handleFromChange = (e: ChangeEvent<HTMLInputElement>) => {
        onChange?.({ ...value, from: e.target.value })
    }
    const handleToChange = (e: ChangeEvent<HTMLInputElement>) => {
        onChange?.({ ...value, to: e.target.value })
    }
    return (
        <div className='flex items-center gap-2'>
            <TimePicker
                max={value.to}
                step={300}
                value={value.from}
                onChange={handleFromChange}
            ></TimePicker>
            <p>〜</p>
            <TimePicker
                min={value.from}
                step={300}
                value={value.to}
                onChange={handleToChange}
            ></TimePicker>
        </div>
    )
}

export default TimeRangePicker
