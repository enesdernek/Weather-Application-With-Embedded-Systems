package com.enesdernek.weather_api.service.abstracts;

import java.util.List;

import com.enesdernek.weather_api.dto.WeatherDto;
import com.enesdernek.weather_api.dto.WeatherDtoIU;

public interface IWeatherService {
	
	public WeatherDto create(WeatherDtoIU dto);
	
	public List<WeatherDto> findTop12ByOrderByTimestampDesc();

}
