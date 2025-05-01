package com.enesdernek.weather_api.service.concretes;

import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;

import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.enesdernek.weather_api.dto.WeatherDto;
import com.enesdernek.weather_api.dto.WeatherDtoIU;
import com.enesdernek.weather_api.model.Weather;
import com.enesdernek.weather_api.repository.WeatherRepository;
import com.enesdernek.weather_api.service.abstracts.IWeatherService;

@Service
public class WeatherService implements IWeatherService{
	
	@Autowired
	private WeatherRepository weatherRepository;
	
	public WeatherDto convertToDto(Weather weather) {
	    WeatherDto weatherDto = new WeatherDto();
	    BeanUtils.copyProperties(weather, weatherDto);

	    // timestamp'ı manuel olarak formatla
	    if (weather.getTimestamp() != null) {
	        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
	        weatherDto.setTimestamp(weather.getTimestamp().format(formatter));
	    }

	    return weatherDto;
	}

	@Override
	public WeatherDto create(WeatherDtoIU weatherDtoIU) {
		
		Weather weather = new Weather();
		BeanUtils.copyProperties(weatherDtoIU, weather);
		Weather savedWeather = this.weatherRepository.save(weather);
		
		WeatherDto weatherDto = convertToDto(savedWeather);
		
		return weatherDto;
		
	}

	@Override
	public List<WeatherDto> findTop12ByOrderByTimestampDesc(){
		
		List<Weather> weathers = this.weatherRepository.findTop12ByOrderByTimestampDesc();
		List<WeatherDto> weatherDtos= new ArrayList<>();
		
		for(Weather weather: weathers) {
			WeatherDto weatherDto = convertToDto(weather);
			weatherDtos.add(weatherDto);	
		}
		
		return weatherDtos;
	}

}
