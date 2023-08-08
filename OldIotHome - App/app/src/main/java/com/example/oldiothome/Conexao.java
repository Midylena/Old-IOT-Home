package com.example.oldiothome;

import android.os.AsyncTask;
import android.util.Log;

import com.google.gson.Gson;

import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.Scanner;

public class Conexao extends AsyncTask<Void, Void, Historico> {
    private static final String TAG = "Servidor";
    @Override
    protected Historico doInBackground(Void... voids) {
        StringBuilder resposta = new StringBuilder();
        try {
            URL url = new URL("http://192.168.0.120:8080/historicoOldIotHome/get");
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("GET");
            connection.setRequestProperty("Content-Type","application/json");
            connection.setConnectTimeout(5000);
            connection.connect();
            Scanner scanner = new Scanner(url.openStream());
            while (scanner.hasNext()){
                resposta.append(scanner.next());
            }
        } catch (MalformedURLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        String str = String.valueOf(resposta);
        Log.i(TAG, str);
        str = str.replace("[", "").replace("]","");
        Log.i(TAG, str);
        return new Gson().fromJson(str,Historico.class);
    }
}
