import { FaRegTrashAlt } from 'react-icons/fa'

import { Button } from '../../atoms/Button'
import { InputWithLabel } from '../../molecules/InputWithLabel'

interface SpotFormProps {
    onChange?: (values: string[]) => void
    values?: string[]
}

const SpotForm = ({ values = [''], onChange, ...props }: SpotFormProps) => {
    const handleChange = (idx: number, value: string) => {
        const newValues = [...values]
        newValues[idx] = value
        onChange?.(newValues)
    }
    const handleAdd = () => {
        const newValues = [...values, '']
        onChange?.(newValues)
    }
    const handleRemove = (idx: number) => {
        if (values.length === 1) {
            onChange?.([''])
        } else {
            const newValues = [...values]
            newValues.splice(idx, 1)
            onChange?.(newValues)
        }
    }
    return (
        <div className='space-y-4'>
            {values.map((value, idx) => (
                <div key={idx} className='flex items-center gap-4'>
                    <InputWithLabel
                        tabIndex={1}
                        value={value}
                        onChange={(value) =>
                            handleChange(idx, value.target.value)
                        }
                    >
                        {`スポット${idx + 1}`}
                    </InputWithLabel>
                    <button
                        className='text-red-700'
                        onClick={() => handleRemove(idx)}
                    >
                        <FaRegTrashAlt />
                    </button>
                </div>
            ))}
            <Button tabIndex={1} onClick={handleAdd}>
                スポットを追加
            </Button>
        </div>
    )
}

export default SpotForm
