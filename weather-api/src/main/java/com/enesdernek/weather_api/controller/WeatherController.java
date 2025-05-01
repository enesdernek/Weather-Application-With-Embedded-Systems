package com.enesdernek.weather_api.controller;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import com.enesdernek.weather_api.dto.WeatherDto;
import com.enesdernek.weather_api.dto.WeatherDtoIU;
import com.enesdernek.weather_api.service.concretes.WeatherService;

@RestController
@RequestMapping(path="/weather")
@CrossOrigin
public class WeatherController {

	@Autowired
	private WeatherService weatherService;
	
	@PostMapping
	public ResponseEntity<WeatherDto> create(@RequestBody WeatherDtoIU weatherDtoIU) {
		return new ResponseEntity<WeatherDto>(this.weatherService.create(weatherDtoIU),HttpStatus.CREATED);
	}
	
	@GetMapping
	public ResponseEntity<List<WeatherDto>> findTop12ByOrderByTimestampDesc() throws InterruptedException{
		Thread.sleep(500);
		return new ResponseEntity<List<WeatherDto>>(this.weatherService.findTop12ByOrderByTimestampDesc(),HttpStatus.OK);
	}
}
