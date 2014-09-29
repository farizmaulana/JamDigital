/** EL-4012 Perancangan Sistem Embedded                                                   
/** Fariz Maulana                                       
/** 13211034                                            
/** Electrical Engineering '11                          
/** Bandung Institute of Technology                     
/** Deskripsi :
    Proyek ini merupakan contoh implementasi sebuah FSM Jam Digital dalam bahasa C dengan fitur update jam dan tanggal.
    Kode program hanya dibuat untuk menunjukkan alur perpindahan state saja (fungsi jam digital tidak dibuat).
    Proyek ini terdiri dari 3 buah file utama dan modul cunit.
    Modul cunit digunakan untuk pengujian proyek secara fungsional. Untuk keterangan lebih lanjut silahkan kunjungi laman resminya     pada tautan berikut http://cunit.sourceforge.net/documentation.html
    Tiga buah file utama tersebut adalah :
    - fsm.c  : File ini berisi fungsi FSM jam digital. 
               Pada FSM yang dibuat, terdapat dua buah superstate (variabel state) yaitu STATE_SETTING dan STATE_TIMEKEEPING. 
               Masing-masing superstate tersusun atas beberapa buah state (variabel substate). Pada superstate STATE_SETTING, 
               terdapat state SET_HOUR, SET_MINUTE dan SET_SECOND. State SET_HOUR akan berisi fungsi untuk melakukan update jam,
               state SET_MINUTE untuk melakukan update menit dan state SET_SECOND untuk merubah detik Jam Digital. Sedangkan
               superstate STATE_TIMEKEEPING terdiri dari state KEEP_TIME dan KEEP_DATE. State KEEP_TIME merupakan state yang 
               berfungsi untuk melakukan perhitungan jam dan menyimpan keadaannya sedangkan state KEEP_DATE bertanggung jawab 
               terhadap perhitungan tanggal.
    - fsm.h  : File ini merupakan header file dari fsm.c
               Pada file ini terdapat bagian preprosesor, purwarupa fungsi dan deklarasi makro atau konstanta yang dipakai.
    - main.c : File ini berisi kode untuk melakukan pengujian terhadap FSM yang dibuat.
               Pengujian dilakukan dengan memberikan nilai input dan kondisi state awal. Pengujian akan dinyatakan berhasil 
               apabila dengan nilai input dan kondisi state awal yang diberikan kondisi state selanjutnya sama antara yang
               dinyatakan pada fungsi CU_ASSERT() dengan fsm.
/** Struktur direktori
    ./common
      -- fsm.c
      -- fsm.h
    ./cunit
      --
    ./JamDigital
      -- main.c
    
