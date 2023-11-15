import { useState } from 'react'

import InputWithLabel from './InputWithLabel'

import type { Meta, StoryObj } from '@storybook/react'

// More on how to set up stories at: https://storybook.js.org/docs/react/writing-stories/introduction#default-export
const meta = {
    // More on argTypes: https://storybook.js.org/docs/react/api/argtypes
    argTypes: {},

    args: { children: 'スポット1' },

    component: InputWithLabel,

    parameters: {
        // Optional parameter to center the component in the Canvas. More info: https://storybook.js.org/docs/react/configure/story-layout
        layout: 'centered',
    },

    // This component will have an automatically generated Autodocs entry: https://storybook.js.org/docs/react/writing-docs/autodocs
    tags: ['autodocs'],
} satisfies Meta<typeof InputWithLabel>

export default meta
type Story = StoryObj<typeof meta>

export const Default: Story = {
    args: {},
}

export const UseState: Story = {
    render: (args) => {
        const [value, setValue] = useState('')
        return (
            <div className='space-y-2'>
                <p>value is : {value}</p>
                <InputWithLabel
                    value={value}
                    onChange={(e) => setValue(e.target.value)}
                    {...args}
                ></InputWithLabel>
            </div>
        )
    },
}
