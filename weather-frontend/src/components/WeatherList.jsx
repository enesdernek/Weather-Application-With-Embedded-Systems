import React, { useEffect, useState } from 'react'
import Table from '@mui/material/Table';
import TableBody from '@mui/material/TableBody';
import TableContainer from '@mui/material/TableContainer';
import TableHead from '@mui/material/TableHead';
import TableRow from '@mui/material/TableRow';
import Paper from '@mui/material/Paper';
import { styled } from '@mui/material/styles';
import TableCell, { tableCellClasses } from '@mui/material/TableCell';
import { useDispatch, useSelector } from 'react-redux';
import { getAllWeatherData } from '../redux/slices/weatherSlice';
import Weather from './Weather';
import CircularProgress from '@mui/material/CircularProgress';




function WeatherList() {

  const weathers = useSelector((state) => state.weather.weathers)
  const dispatch = useDispatch()
  const [initialLoading, setInitialLoading] = useState(true);


  useEffect(() => {
    dispatch(getAllWeatherData()).then(() => setInitialLoading(false));

    const interval = setInterval(() => {
      dispatch(getAllWeatherData());
    }, 10000);

    return () => clearInterval(interval);
  }, []);


  const StyledTableCell = styled(TableCell)(({ theme }) => ({
    [`&.${tableCellClasses.head}`]: {
      backgroundColor: "orange",
      color: "black",
      fontWeight: "bold"
    },
    [`&.${tableCellClasses.body}`]: {
      fontSize: 14,
    },
  }));

  if (initialLoading) {
    return (
      <div style={{ display: 'flex', justifyContent: 'center', marginTop: '40px' }}>
        <CircularProgress color="success" />
      </div>
    );
  }


  return (
    <TableContainer component={Paper} sx={{ marginTop: "20px" }}>
      <Table sx={{ minWidth: 700 }} aria-label="customized table">
        <TableHead >
          <TableRow >
            <StyledTableCell>Tarih</StyledTableCell>
            <StyledTableCell align="center">Hava Durumu</StyledTableCell>
            <StyledTableCell align="center">Sıcaklık (°C)</StyledTableCell>
            <StyledTableCell align="center">Nem (%)</StyledTableCell>
            <StyledTableCell align="center">Basınç (hPa)</StyledTableCell>
          </TableRow>
        </TableHead>
        <TableBody>
          {
            weathers && weathers.map((weather) => (
              <Weather key={weather.weatherId} weather={weather} />
            ))
          }

        </TableBody>
      </Table>
    </TableContainer>
  )
}

export default WeatherList