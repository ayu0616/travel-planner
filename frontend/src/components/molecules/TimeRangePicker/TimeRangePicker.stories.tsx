import { useState } from 'react'

import TimeRangePicker, { TimeRange } from './TimeRangePicker'

import type { Meta, StoryObj } from '@storybook/react'

// More on how to set up stories at: https://storybook.js.org/docs/react/writing-stories/introduction#default-export
const meta = {
    // More on argTypes: https://storybook.js.org/docs/react/api/argtypes
    argTypes: {},
    component: TimeRangePicker,
    parameters: {
        // Optional parameter to center the component in the Canvas. More info: https://storybook.js.org/docs/react/configure/story-layout
        layout: 'centered',
    },
    // This component will have an automatically generated Autodocs entry: https://storybook.js.org/docs/react/writing-docs/autodocs
    tags: ['autodocs'],
} satisfies Meta<typeof TimeRangePicker>

export default meta
type Story = StoryObj<typeof meta>

export const Default: Story = {
    args: {},
    render: (args) => {
        const [value, setValue] = useState<TimeRange>({
            from: undefined,
            to: undefined,
        })
        return (
            <div className='space-y-4'>
                <p>
                    value: {value.from ?? 'undefined'}〜
                    {value.to ?? 'undefined'}
                </p>
                <TimeRangePicker
                    value={value}
                    onChange={setValue}
                ></TimeRangePicker>
            </div>
        )
    },
}
