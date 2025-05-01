import React from 'react'
import AppBar from '@mui/material/AppBar';
import Toolbar from '@mui/material/Toolbar';
import Typography from '@mui/material/Typography';
import IconButton from '@mui/material/IconButton';
import MenuIcon from '@mui/icons-material/Menu';
import SunnyIcon from '@mui/icons-material/Sunny';
function Header() {
    return (
        <AppBar position="static" sx={{ bgcolor: '#fff',color:"black"}}>
            <Toolbar variant="dense">
                <IconButton edge="start" color="inherit" aria-label="menu" sx={{ mr: 2 }}>
                    <SunnyIcon sx={ {color:"orange"}} />
                </IconButton>
                <Typography variant="h6" color="inherit" component="div">
                    Hava Durumu 
                </Typography>
            </Toolbar>
        </AppBar>
    )
}

export default Header