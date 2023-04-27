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
@RequestMapping("/historico")
public class HistoricoRest {
	
	@Autowired
	private HistoricoDao historicoDao;
	
	@GetMapping
	public List<Historico> get(){
		return historicoDao.findAll();
	}
	
	@GetMapping("/get")
	public Collection<Historico> hist(){
		return historicoDao.hist();
	}
	
	@PostMapping("/post")
	public String post(@RequestBody Historico historico) {
		historicoDao.save(historico);
		return "ENVIADO";
	}
}
