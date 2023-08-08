package com.example.oldiothome;

public class Historico {
    private Long id;
    private String comodo;
    private Long numComodo;

    private String tag;

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getComodo() {
        return comodo;
    }

    public void setComodo(String comodo) {
        comodo = comodo;
    }

    public Long getNumComodo() {
        return numComodo;
    }

    public void setNumComodo(Long numComodo) {
        numComodo = numComodo;
    }

    public String getTag() {
        return tag;
    }

    public void setTag(String tag) {
        tag = tag;
    }

    @Override
    public String toString() {
        return  "id = " + getId() +
                "\ncomodo = " + getComodo() +
                "\nnumComodo = " + getNumComodo() +
                "\ntag = " + getTag();
    }

    public String toStringNumComodo() {
        return  "numComodo = " + getNumComodo();
    }
    public String toStringTag() {
        return  "tag = " + getTag();
    }
}