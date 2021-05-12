package com.github.pperal.citiesapi.countries.repository;

import com.github.pperal.citiesapi.countries.Country;
import org.springframework.data.jpa.repository.JpaRepository;

public interface CountryRepository extends JpaRepository<Country, Long> {
}
