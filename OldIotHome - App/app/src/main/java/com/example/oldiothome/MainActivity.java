package com.example.oldiothome;

import static com.example.oldiothome.R.id.button_Cozinha;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.util.concurrent.ExecutionException;

public class MainActivity extends AppCompatActivity {
        final String TAG = "Classe Conexão";
        final Handler handler = new Handler();

        Button buttonSala;
        Button buttonCozinha;
        Button buttonQuarto;
        Button buttonBanheiro;
        TextView textViewTag;

        @Override
        protected void onCreate (Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.activity_main);

            buttonSala = findViewById(R.id.button_Sala);
            buttonCozinha = findViewById(R.id.button_Cozinha);
            buttonQuarto = findViewById(R.id.button_Quarto);
            buttonBanheiro = findViewById(R.id.button_Banheiro);
            buttonBanheiro = findViewById(R.id.button_Banheiro);
            textViewTag = findViewById(R.id.textView_Tag);

            //handler.postDelayed(atualizar, 1000);
            atualizar.run();
        }


        private Runnable atualizar = new Runnable() {
            @Override
            public void run() {
                    Conexao conexao = new Conexao();

                    try {
                        Historico historico = conexao.execute().get();
                        Log.i(TAG, historico.toString());
                        Log.i(TAG, historico.toStringTag());
                        Log.i(TAG, historico.toStringNumComodo());
                        textViewTag.setText(historico.getTag());
                        if (historico.getNumComodo() == 1) {
                            buttonSala.setBackgroundTintList(getResources().getColorStateList(R.color.Verde));
                            buttonCozinha.setBackgroundTintList(getResources().getColorStateList(R.color.Azul));
                            buttonQuarto.setBackgroundTintList(getResources().getColorStateList(R.color.Azul));
                            buttonBanheiro.setBackgroundTintList(getResources().getColorStateList(R.color.Azul));
                        } else if (historico.getNumComodo() == 2) {
                            buttonSala.setBackgroundTintList(getResources().getColorStateList(R.color.Azul));
                            buttonCozinha.setBackgroundTintList(getResources().getColorStateList(R.color.Verde));
                            buttonQuarto.setBackgroundTintList(getResources().getColorStateList(R.color.Azul));
                            buttonBanheiro.setBackgroundTintList(getResources().getColorStateList(R.color.Azul));
                        } else if (historico.getNumComodo() == 3) {
                            buttonSala.setBackgroundTintList(getResources().getColorStateList(R.color.Azul));
                            buttonCozinha.setBackgroundTintList(getResources().getColorStateList(R.color.Azul));
                            buttonQuarto.setBackgroundTintList(getResources().getColorStateList(R.color.Verde));
                            buttonBanheiro.setBackgroundTintList(getResources().getColorStateList(R.color.Azul));
                        } else if (historico.getNumComodo() == 4) {
                            buttonSala.setBackgroundTintList(getResources().getColorStateList(R.color.Azul));
                            buttonCozinha.setBackgroundTintList(getResources().getColorStateList(R.color.Azul));
                            buttonQuarto.setBackgroundTintList(getResources().getColorStateList(R.color.Azul));
                            buttonBanheiro.setBackgroundTintList(getResources().getColorStateList(R.color.Verde));
                        }
                    } catch (
                            ExecutionException e) {
                        throw new RuntimeException(e);
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                handler.postDelayed(this, 1000);
                }
            };
        }