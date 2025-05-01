import { configureStore } from '@reduxjs/toolkit'
import  weatherSlice  from './slices/weatherSlice'

export const store = configureStore({
  reducer: {
    weather:weatherSlice
  },
})