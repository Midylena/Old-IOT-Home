package com.mechachieve.oldiothome;

import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;

@Entity
public class HistoricoOldIotHome {
	
	private Long id;
	
	private String Comodo;
	
	private Long NumComodo;
	
	private String Tag;
	
	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	public Long getId() {
		return id;
	}

	public void setId(Long id) {
		this.id = id;
	}

	public String getComodo() {
		return Comodo;
	}

	public void setComodo(String comodo) {
		Comodo = comodo;
	}

	public Long getNumComodo() {
		return NumComodo;
	}

	public void setNumComodo(Long numComodo) {
		NumComodo = numComodo;
	}
	
	public String getTag() {
		return Tag;
	}

	public void setTag(String tag) {
		Tag = tag;
	}
}
