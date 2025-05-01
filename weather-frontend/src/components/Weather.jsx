import React from 'react'
import { styled } from '@mui/material/styles';
import TableRow from '@mui/material/TableRow';
import TableCell, { tableCellClasses } from '@mui/material/TableCell';
import { FaCloudRain } from "react-icons/fa";
import { FaCloudSun } from "react-icons/fa";
import { FaSun } from "react-icons/fa";





function Weather({ weather }) {

  const StyledTableRow = styled(TableRow)(({ theme }) => ({
    '&:nth-of-type(odd)': {
      backgroundColor: theme.palette.action.hover,
    },
    // hide last border
    '&:last-child td, &:last-child th': {
      border: 0,
    },
  }));

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

  return (

    <StyledTableRow key={weather.weatherId}>
      <StyledTableCell component="th" scope="row">
        {weather.timestamp}
      </StyledTableCell>
      <StyledTableCell align="center">
        {weather.raining ? (
          <FaCloudRain style={{ fontSize: "26px", color: "#1E90FF" }} />
        ) : weather.temperature >= 23 ? (
          <FaSun style={{ fontSize: "26px", color: "#FFA500" }} />
        ) : (
          <FaCloudSun style={{ fontSize: "26px", color: "#808080" }} />
        )}
      </StyledTableCell>
      <StyledTableCell align="center">{weather.temperature}</StyledTableCell>
      <StyledTableCell align="center">{weather.humidity}</StyledTableCell>
      <StyledTableCell align="center">{weather.pressure}</StyledTableCell>
    </StyledTableRow>

  )
}

export default Weather