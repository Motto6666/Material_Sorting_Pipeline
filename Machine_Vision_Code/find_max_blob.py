#计算出最大色块函数
def find_max_blob(blobs):
    if(blobs):
        max_pixels=0
        for blob in blobs:
            if blob[4] > max_pixels:
                max_blob=blob
                max_pixels = blob[4]
        return max_blob
    else:
        return None
