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

- jumlah worker : 1
- alamat server : localhost:80
- tingkat konkurensi : 10000

1.3 Hasil

| Ukuran file        | Waktu rata-rata (ms)           | Penggunaan CPU (%) | Penggunaan RAM (%)|
| ------------- |:-------------:|:-------------:|:-------------:|
| 500 B    | 487 | 14.6 | 0.1 |
| 20 KB      | 579      | 14.7 | 0.1 |

server
  - worker = 4
  500B
    - cpu : ?
    - ram : ?
    - time_mean : 119
  20KB
    - cpu : ?
    - ram : ?
    - time_mean : 157


