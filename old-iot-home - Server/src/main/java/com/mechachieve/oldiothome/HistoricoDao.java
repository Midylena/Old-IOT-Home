package com.mechachieve.oldiothome;

import java.util.Collection;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.http.ResponseEntity;


public interface HistoricoDao extends JpaRepository<Historico, Long>{
	
	@Query(value = "select * from historico where id = (select max(id) from historico)", nativeQuery = true)
	Collection<Historico> hist();
}
