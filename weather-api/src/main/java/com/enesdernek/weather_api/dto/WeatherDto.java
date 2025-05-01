package com.enesdernek.weather_api.dto;

import java.time.LocalDateTime;


import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class WeatherDto {

	private Long weatherId;
	
	private float temperature;
	
	private float humidity;
	
	private boolean isRaining;

    private LocalDateTime timestamp;

}
