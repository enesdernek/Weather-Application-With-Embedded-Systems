import { Box, Container } from '@mui/material'
import React from 'react'
import Header from '../layout/Header'
import MainContent from '../layout/MainContent'

function Home() {
    return (
        <Container fixed>
            <Header/>
            <MainContent />
        </Container>
    )
}

export default Home