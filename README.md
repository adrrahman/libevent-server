# Tugas PAT 1: libevent library

Kelompok:

| Nama        | NIM           |
| ------------- |:-------------:|
| Abdurrahman      | 13515024 |
| Muhammad Umar Fariz Tumbuan      | 13515050      |

## Pendahuluan

Tugas yang diberikan adalah:

1. Melakukan benchmark terhadap nginx untuk melakukan 10000 concurrent request terhadap file sebesar 500B dan 20KB.
2. Mengimplementasi sebuah web server menggunakan library event polling low level dan melakukan benchmarking yang sama dengan tugas (1).

## Environment

- OS: Ubuntu 18.04
- CPU : Intel Core I5-6200U (2 core @ 2.8 Ghz)
- RAM : 8 GB

## Hasil Benchmark

### 1. Nginx

1.1 Pendahuluan

Tools benchmark yang digunakan adalah Apache Benchmark. Input cli yang digunakan: 

```
ab -n 10000 -c 10000 [alamat server]
```

Nilai yang menjadi perhatian dapat dilihat pada gambar 1. Gambar tersebut menunjukkan waktu yang digunakan untuk menyelesaikan request. Untuk melihat penggunaan cpu dan ram, digunakan command:

```
top | grep nginx
```


| ![alt text](https://github.com/adrrahman/libevent-server/blob/master/img/benchmark.png "benchmark image")        |
| ------------- |
| Gambar 1      |

1.2 Konfigurasi

- jumlah worker : 4
- alamat server : localhost:80
- tingkat konkurensi : 10000

1.3 Hasil

| Ukuran file        | Waktu rata-rata (ms)           | Penggunaan CPU (%) | Penggunaan RAM (%)|
| ------------- |:-------------:|:-------------:|:-------------:|
| 500 B    | 487 | 14.6 | 0.1 |
| 20 KB      | 579      | 14.7 | 0.1 |

### 2. Web Server dengan Libevent

2.1 Pendahuluan

Implementasi web server kami adopsi dari sebuah [blog bernama kukuruku.com] yang membahas program web server menggunakan c.(https://kukuruku.co/post/lightweight-http-server-in-less-than-40-lines-on-libevent-and-c-11/). Program dibuat dengan menggunakan library libevent dan pthread. Ada 2 jenis implementasi yang dibuat, single-threaded dan multi-threaded dengan prethreading. Kami melakukan benchamark hanya terhadap program yang multi-threaded.

Untuk mengompilasi program gunakan command:

```
# untuk single threaded. Menghasilkan program bernama server
make 

# untuk multi threaded dengan prethreading. Menghasilkan program bernama pre_server
make pre
```

Untuk menjalankan server gunakan command berikut. Server akan selalu berjalan pada port 5555.

```
./pre_server 0.0.0.0
```

Untuk melakukan request file, gunakan url berikut:

```
0.0.0.0:5555/?filename=resource/500B.html
0.0.0.0:5555/?filename=resource/20KB.html
```

Akhirnya, untuk melakukan testing digunakan dua command berikut:

```
ab -n 10000 -c 10000 0.0.0.0:5555/?filename=resource/500B.html
ab -n 10000 -c 10000 0.0.0.0:5555/?filename=resource/20KB.html
```

2.2 Konfigurasi

- jumlah worker : 4
- alamat server : 0.0.0.0:80
- tingkat konkurensi : 10000

1.3 Hasil

| Ukuran file        | Waktu rata-rata (ms)           | Penggunaan CPU (%) | Penggunaan RAM (%)|
| ------------- |:-------------:|:-------------:|:-------------:|
| 500 B    | 127 | 25.7 | 0.7 |
| 20 KB      | 205      | 47.7 | 0.9 |

## Pembahasan

Dari hasil di atas, waktu yang dibutuhkan untuk melakukan 10000 concurrent request cenderung cepat (maksimal sekitar 500 ms). Faktor utama dari kecepatan ini tentu saja karena benchmark dilakukan terhadap namespace localhost. Namun web server berbasis libevent dapat menyelesaikan proses hampir selalu 2 kali lipat lebih cepat.

Menurut kami perbedaan mencolok terjadi karena konfigurasi default nginx meberikan batasan untuk performa. Melalui apache benchmark kita dapat melihat transfer rate yang dihasil kedua jenis percobaan. Nginx memilki transfer rate sekitar 6-7 MB/sec, sedangkan web server berbasis libevent memiliki nilai sekitar 200 MB /sec. Namun akibatnya program web server menggunakan resource yang sangat besar (sampai hampir 50% cpu dan 1% ram). Asumsi kami nginx sengaja memiliki konfigurasi tersebut untuk mencegah server kehabisan resource untuk proses lain.

