package com.mechachieve.oldiothome;

import java.util.Collection;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/historicoOldIotHome")
public class HistoricoRestOldIotHome {
	
	@Autowired
	private HistoricoDaoOldIotHome historicoDao;
	
	@GetMapping
	public List<HistoricoOldIotHome> get(){
		return historicoDao.findAll();
	}
	
	@GetMapping("/get")
	public Collection<HistoricoOldIotHome> hist(){
		return historicoDao.hist();
	}
	
	@PostMapping("/post")
	public String post(@RequestBody HistoricoOldIotHome historico) {
		historicoDao.save(historico);
		return "ENVIADO";
	}
}
