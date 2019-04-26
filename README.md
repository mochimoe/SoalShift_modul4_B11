# Penjelasan Modul 4


### Nomer 1
-  Pada soal diminta untuk mengenkripsi menggunakan Caesar Chiper, namun dikarenakan terlalu mudah maka karakter list di    ekspansi , tidak hanya alphabet dan diacak . Berikut list characternya :

    ``` qE1~ YMUR2"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\8s;g<{3.u*W-0```
    
    Misalkan ada file bernama ``“halo”`` di dalam folder ``“INI_FOLDER”``, dan key yang dipakai adalah 17, maka:
```“INI_FOLDER/halo”``` saat belum di-mount maka akan bernama ``“n,nsbZ]wio/QBE#”``, saat telah di-mount maka akan otomatis terdekripsi kembali menjadi ``“INI_FOLDER/halo”`` .

   Perhatian: Karakter ‘/’ adalah karakter ilegal dalam penamaan file atau folder dalam *NIX, maka dari itu dapat diabaikan

#### Solusi 


### Nomer 2

+ Semua file video yang tersimpan secara terpecah-pecah (splitted) harus secara otomatis tergabung (joined) dan diletakkan dalam folder “Videos”
Urutan operasi dari kebutuhan ini adalah:
  - Tepat saat sebelum file system di-mount
      - Secara otomatis folder “Videos” terbuat di root directory file system
      - Misal ada sekumpulan file pecahan video bernama “computer.mkv.000”, “computer.mkv.001”, “computer.mkv.002”, dst. Maka           secara otomatis file pecahan tersebut akan di-join menjadi file video “computer.mkv”
        Untuk mempermudah kalian, dipastikan hanya video file saja yang terpecah menjadi beberapa file. File pecahan tersebut           dijamin terletak di root folder fuse
      - Karena mungkin file video sangat banyak sehingga mungkin saja saat menggabungkan file video, file system akan                   membutuhkan waktu yang lama untuk sukses ter-mount. Maka pastikan saat akan menggabungkan file pecahan video, file             system akan membuat 1 thread/proses(fork) baru yang dikhususkan untuk menggabungkan file video tersebut
      - Pindahkan seluruh file video yang sudah ter-join ke dalam folder “Videos”
      - Jangan tampilkan file pecahan di direktori manapun
  - Tepat saat file system akan di-unmount
      - Hapus semua file video yang berada di folder “Videos”, tapi jangan hapus file pecahan yang terdapat di root directory           file system
      - Hapus folder “Videos” 
