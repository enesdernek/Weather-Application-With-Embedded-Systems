package com.enesdernek.weather_api.repository;

import java.util.List;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import com.enesdernek.weather_api.model.Weather;

@Repository
public interface WeatherRepository extends JpaRepository<Weather, Long>{

	public List<Weather> findTop12ByOrderByTimestampDesc();


	
}
