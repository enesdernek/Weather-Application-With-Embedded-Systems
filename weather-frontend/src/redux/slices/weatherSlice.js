import { createAsyncThunk, createSlice } from '@reduxjs/toolkit'
import axios from "axios"

const initialState = {
    weathers: [],
    loading:false
}

const BASIC_PATH = "http://localhost:8080/weather"

export const getAllWeatherData = createAsyncThunk(
    'weather/getAll',
    async () => {
        const response = await axios.get(BASIC_PATH)
        return response.data
    }

)

export const weatherSlice = createSlice({
    name: 'weather',
    initialState,
    reducers: {
      
    },
    extraReducers: (builder) => {
        builder.addCase(getAllWeatherData.fulfilled, (state, action) => {
            state.weathers = action.payload
            state.loading=false
        })
        builder.addCase(getAllWeatherData.pending, (state, action) => {
            state.loading=true
        })
        builder.addCase(getAllWeatherData.rejected, (state, action) => {
            state.loading=false
        })
    }
})

export const { } = weatherSlice.actions

export default weatherSlice.reducer