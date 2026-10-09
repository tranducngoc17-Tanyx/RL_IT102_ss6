#include <stdio.h>
#include <string.h>

int main() {
    // Khai bao cac mang song song va bien dem
    const int MAX = 100;
    char maPhieu[100][20];
    char maSach[100][20];
    int soNgayMuon[100];
    
    int soLuong = 0; // So luong phieu muon hien tai
    int chon = 0;

    do {
        printf("\n================ HET HONG QUAN LY MUON TRA SACH (LOGISTICS) ================\n");
        printf("1. Them moi phieu muon sach (Create)\n");
        printf("2. Hien thi danh sach phieu muon & Tien phat qua han (Read)\n");
        printf("3. Cap nhat so ngay muon sach (Update)\n");
        printf("4. Xac nhan tra sach / Xoa phieu muon (Delete)\n");
        printf("5. Thoat chuong trinh\n");
        printf("===========================================================================\n");
        printf("Lua chon cua ban (1-5): ");
        scanf("%d", &chon);

        // Lam sach bo dem ban phim sau khi scan so
        while (getchar() != '\n');

        switch (chon) {
            case 1: { // 1. THEM MOI PHIEU MUON
                printf("\n--- THEM MOI PHIEU MUON ---\n");
                
                if (soLuong >= MAX) {
                    printf("Bo nho danh sach da day, khong the them moi!\n");
                    break;
                }

                // Nhap va kiem tra trung lap Ma phieu
                char maNhap[20];
                int biTrung = 0;
                do {
                    biTrung = 0;
                    printf("Nhap ma phieu: ");
                    fgets(maNhap, sizeof(maNhap), stdin);
                    maNhap[strcspn(maNhap, "\n")] = '\0'; // Xoa ky tu '\n'

                    // Kiem tra chuoi rong
                    if (strlen(maNhap) == 0) {
                        printf("Ma phieu khong duoc de rong! Vui long nhap lai.\n");
                        biTrung = 1;
                        continue;
                    }

                    // Tim kiem tuyen tinh kiem tra trung lap
                    for (int i = 0; i < soLuong; i++) {
                        if (strcmp(maPhieu[i], maNhap) == 0) {
                            printf("Ma phieu da ton tai trong he thong!\n");
                            biTrung = 1;
                            break;
                        }
                    }
                } while (biTrung);

                // Luu Ma phieu
                strcpy(maPhieu[soLuong], maNhap);

                // Nhap Ma sach
                printf("Nhap ma sach: ");
                fgets(maSach[soLuong], sizeof(maSach[soLuong]), stdin);
                maSach[soLuong][strcspn(maSach[soLuong], "\n")] = '\0';

                // Nhap So ngay muon (> 0)
                int ngay = 0;
                do {
                    printf("Nhap so ngay muon: ");
                    scanf("%d", &ngay);
                    while (getchar() != '\n'); // Lam sach bo dem

                    if (ngay <= 0) {
                        printf("So ngay muon phai la so nguyen lon hon 0! Vui long nhap lai.\n");
                    }
                } while (ngay <= 0);

                soNgayMuon[soLuong] = ngay;
                soLuong++; // Tang so luong phieu

                printf("Them moi phieu muon thanh cong!\n");
                break;
            }

            case 2: { // 2. HIEN THI DANH SACH & TINH TIEN PHAT
                printf("\n================================ DANH SACH PHIEU MUON ================================\n");
                if (soLuong == 0) {
                    printf("Danh sach phieu muon hien dang rong!\n");
                } else {
                    printf("%-5s | %-15s | %-15s | %-13s | %-15s | %-15s\n", 
                           "STT", "MA PHIEU", "MA SACH", "SO NGAY MUON", "TRANG THAI", "TIEN PHAT (VND)");
                    printf("--------------------------------------------------------------------------------------\n");

                    long tongTienPhat = 0;
                    for (int i = 0; i < soLuong; i++) {
                        int ngayQuaHan = 0;
                        long tienPhat = 0;
                        char trangThai[15];

                        if (soNgayMuon[i] > 14) {
                            ngayQuaHan = soNgayMuon[i] - 14;
                            tienPhat = (long)ngayQuaHan * 5000;
                            strcpy(trangThai, "QUA HAN");
                        } else {
                            tienPhat = 0;
                            strcpy(trangThai, "DUNG HAN");
                        }

                        tongTienPhat += tienPhat;

                        printf("%-5d | %-15s | %-15s | %-13d | %-15s | %-15ld\n", 
                               i + 1, maPhieu[i], maSach[i], soNgayMuon[i], trangThai, tienPhat);
                    }
                    printf("--------------------------------------------------------------------------------------\n");
                    printf("Tong tien phat phai thu: %ld VND\n", tongTienPhat);
                }
                break;
            }

            case 3: { // 3. CAP NHAT SO NGAY MUON
                printf("\n--- CAP NHAT SO NGAY MUON ---\n");
                if (soLuong == 0) {
                    printf("Danh sach phieu muon hien dang rong!\n");
                    break;
                }

                char timMa[20];
                printf("Nhap ma phieu cua phieu muon can gia han/cap nhat: ");
                fgets(timMa, sizeof(timMa), stdin);
                timMa[strcspn(timMa, "\n")] = '\0';

                int pos = -1;
                // Tim kiem tuyen tinh
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], timMa) == 0) {
                        pos = i;
                        break;
                    }
                }

                if (pos == -1) {
                    printf("Khong tim thay ma phieu trong he thong!\n");
                } else {
                    printf("So ngay muon hien tai cua phieu %s la: %d\n", maPhieu[pos], soNgayMuon[pos]);

                    int ngayMoi = 0;
                    do {
                        printf("Nhap so ngay muon moi: ");
                        scanf("%d", &ngayMoi);
                        while (getchar() != '\n'); // Lam sach bo dem

                        if (ngayMoi <= 0) {
                            printf("So ngay muon phai la so nguyen lon hon 0! Vui long nhap lai.\n");
                        }
                    } while (ngayMoi <= 0);

                    soNgayMuon[pos] = ngayMoi;
                    printf("Cap nhat so ngay muon thanh cong!\n");
                }
                break;
            }

            case 4: { // 4. XAC NHAN TRA SACH / XOA PHIEU MUON
                printf("\n--- XAC NHAN TRA SACH / XOA PHIEU MUON ---\n");
                if (soLuong == 0) {
                    printf("Danh sach phieu muon hien dang rong!\n");
                    break;
                }

                char timMa[20];
                printf("Nhap ma phieu xac nhan tra/xoa: ");
                fgets(timMa, sizeof(timMa), stdin);
                timMa[strcspn(timMa, "\n")] = '\0';

                int pos = -1;
                // Tim kiem tuyen tinh
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], timMa) == 0) {
                        pos = i;
                        break;
                    }
                }

                if (pos == -1) {
                    printf("Khong tim thay ma phieu me can xoa!\n");
                } else {
                    // Thuat toan don mang tu pos den soLuong - 2
                    for (int i = pos; i < soLuong - 1; i++) {
                        strcpy(maPhieu[i], maPhieu[i + 1]);
                        strcpy(maSach[i], maSach[i + 1]);
                        soNgayMuon[i] = soNgayMuon[i + 1];
                    }

                    soLuong--; // Giam so luong
                    printf("Xac nhan tra sach va xoa phieu muon thanh cong!\n");
                }
                break;
            }

            case 5:
                printf("\nThoat chuong trinh. Cam on ban da su dung HE THONG QUAN LY MUON TRA SACH (LOGISTICS)!\n");
                break;

            default:
                printf("Lua chon khong hop le, vui long chon lai!\n");
                break;
        }

    } while (chon != 5);

    return 0;
}