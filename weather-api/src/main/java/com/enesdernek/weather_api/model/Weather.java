package com.enesdernek.weather_api.model;

import java.time.LocalDateTime;

import org.hibernate.annotations.CreationTimestamp;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.Table;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Entity
@Table(name="weather")
@Data
@AllArgsConstructor
@NoArgsConstructor
public class Weather {
	
	@Id
	@GeneratedValue(strategy=GenerationType.IDENTITY)
	private Long weatherId;
	
	private float temperature;
	
	private float humidity;
	
	private boolean isRaining;

	@Column(nullable = false, updatable = false)
    @CreationTimestamp
    private LocalDateTime timestamp;
}
