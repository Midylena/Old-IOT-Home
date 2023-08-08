package com.mechachieve.oldiothome;

import java.util.Collection;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.http.ResponseEntity;


public interface HistoricoDaoOldIotHome extends JpaRepository<HistoricoOldIotHome, Long>{
	
	@Query(value = "select * from historico_old_iot_home where id = (select max(id) from historico_old_iot_home)", nativeQuery = true)
	Collection<HistoricoOldIotHome> hist();
}
