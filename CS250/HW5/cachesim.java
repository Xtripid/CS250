import java.util.*;
import java.lang.Math;
import java.io.*;

public class cachesim {
  static class Block {
    public int lru;
    public int valid;
    public int tag;
    public int dirty;
    public String[] dataBlock;

    public Block() {}
    public Block(int l, int vBit, int t, int dirt, String[] data) {
      lru = l;
      valid = vBit;
      tag = t;
      dirty = dirt;
      dataBlock = data.clone();
    }
    public int getLru() {
      return lru;
    }
    public int getValid() {
      return valid;
    }
    public int getTag() {
      return tag;
    }
    public int getDirty() {
      return dirty;
    }
    public String[] getdataBlock() {
      return dataBlock;
    }
    public void setLru(int l) {
      lru = l;
    }
    public void setValid(int v) {
      valid = v;
    }
    public void setTag(int t) {
      tag = t;
    }
    public void setDirty(int d) {
      dirty = d;
    }
    public void setData(String[] d) {
      dataBlock = d.clone();
    }
    public Block(Block another) {
      valid = another.valid;
      lru = another.lru;
      tag = another.tag;
      dirty = another.dirty;
      dataBlock = another.dataBlock.clone();
    }
  }

  public static String[] main_mem;
  public static int cache_size;
  public static int set_size;
  public static int block_size;
  public static int lru_count;
  public static Block[][] cache_sim;

  public static void create_mem() {
    main_mem = new String[16777216];
    for(int i = 0; i < 16777216; i ++) {
      main_mem[i] = "00";
    }
  }

  public static void create_cache(int csize, int associativity, int bsize) {
    cache_size = csize * 1024;
    set_size = associativity;
    block_size = bsize;
    cache_sim = new Block[cache_size/(block_size*set_size)][set_size];
    String[] zeros = new String[64];
    lru_count = 0;
    for (int k = 0; k < 64; k++) {
      zeros[k] = "00";
    }
    for (int i = 0; i < cache_sim.length; i ++) {
      for (int j = 0; j < cache_sim[0].length; j++) {
        cache_sim[i][j] = new Block();
//        cache_sim[i][j].setValid(0);
//        cache_sim[i][j].setTag(0);
//        cache_sim[i][j].setLru(0);
//        cache_sim[i][j].setDirty(0);
        cache_sim[i][j].setData(zeros);
      }
    }
  }
  public static int getIndex(long address) {
    return (int)((Math.log(cache_size/(block_size*set_size)))/Math.log(2));
  }

  public static int getBlockOffset(long address) {
    return (int)(Math.log(block_size)/Math.log(2));
  }

  public static void cache_store(long address, int size_access, String store) {
    int a = (int)Math.pow(2, getBlockOffset(address)) - 1;
    int b = (int)Math.pow(2, getIndex(address)) - 1;
    int index = (int)((address >> getBlockOffset(address)) & b);
    int bOff = (int)(address & a);
    int tag = (int)((address >> getBlockOffset(address)) >> getIndex(address));
    int toGet = size_access * 2;
    int found = 0;
    for(int i = 0; i < set_size && found == 0; i++) {
      Block currBlock = cache_sim[index][i];
      if (currBlock.getValid() == 1 && currBlock.getTag() == tag) {
        int temp = bOff;
        String[] x = currBlock.getdataBlock();
        for(int j = 0; j < toGet; j=j+2) {
          x[temp] = store.substring(j,j+2);
          temp++;
        }
        currBlock.setData(x);
        currBlock.setDirty(1);
        currBlock.setLru(lru_count);
        currBlock.setTag(tag);
        found = 1;
        cache_sim[index][i] = currBlock;
        System.out.println("store 0x" + String.format("%x", address) + " hit");
        break;
      }
    }
    if(found == 0) {
      int lruBlockInd = 0;
      Block lruBlock = null;
      for(int r = 0; r < set_size; r++) {
        Block cur = cache_sim[index][r];
        if(cur.getValid() == 0) {
          lruBlock = cur;
          found = 1;
          lruBlockInd = r;
          break;
        }
      }
      if(found == 0) {
        lruBlock = cache_sim[index][0];
        for(int k = 0; k < set_size; k++) {
          Block curr_Block = cache_sim[index][k];
          int least = lruBlock.getLru();
          if(curr_Block.getLru() < least) {
            lruBlock = curr_Block;
            least = curr_Block.getLru();
            lruBlockInd = k;
          }
        }
        int y = lruBlock.getdataBlock().length;
        int z = 0;
        if(lruBlock.getDirty() == 1) {
          int placeInMem = (int)((lruBlock.getTag() << getIndex(address)) | index);
//          int placeInMem = (int)((address >> getBlockOffset(address)));
          for(int l = placeInMem; l < placeInMem + y; l++) {
            String[] tem = lruBlock.getdataBlock();
            main_mem[l] = tem[z];
            z++;
          }
        }
      }
      int x = 0;
      String[] tem = new String[block_size];
      int addMoved = (int)address >> getBlockOffset(address);
      for(int m = addMoved; m < addMoved + block_size; m++) {
        tem[x] = main_mem[m];
        x++;
      }
      lruBlock.setData(tem);
      int temp = bOff;
      String[] rep = lruBlock.getdataBlock();
      for(int n = 0; n <toGet; n=n+2) {
        rep[temp] = store.substring(n,n+2);
        temp++;
      }
      lruBlock.setData(rep);
      lruBlock.setDirty(1);
      lruBlock.setValid(1);
      lruBlock.setTag(tag);
      lruBlock.setLru(lru_count);
      found = 1;
      cache_sim[index][lruBlockInd] = lruBlock;
      System.out.println("store 0x" + String.format("%x", address) + " miss");
    }
    lru_count++;
  }

  public static void cache_load(long address, int size_access) {
    int a = (int)Math.pow(2, getBlockOffset(address)) - 1;
    int b = (int)Math.pow(2, getIndex(address)) - 1;
    int index = (int)((address >> getBlockOffset(address)) & b);
    int bOff = (int)(address & a);
    int tag = (int)((address >> getBlockOffset(address)) >> getIndex(address));
    int toGet = size_access * 2;
    int found = 0;
    for(int i = 0; i < set_size && found == 0; i++) {
      Block currBlock = cache_sim[index][i];
      if (currBlock.getValid() == 1 && currBlock.getTag() == tag) {
        int temp = bOff;
        String s = "";
        String[] te = currBlock.getdataBlock();
        for(int j = 0; j < size_access; j++) {
          s = s.concat(te[temp + j]);
        }
        found = 1;
        currBlock.setLru(lru_count);
        cache_sim[index][i] = currBlock;
        System.out.println("load 0x" + String.format("%x", address) + " hit " + s);
        break;
      }
    }
    if(found == 0) {
      Block lruBlock = null;
      int lruBlockInd = 0;
      for(int r = 0; r < set_size; r++) {
        Block cur = cache_sim[index][r];
        if(cur.getValid() == 0) {
          lruBlock = cur;
          found = 1;
          lruBlockInd = r;
          break;
        }
      }
      if(found == 0) {
        lruBlock = cache_sim[index][0];
        for(int k = 0; k < set_size; k++) {
          Block curr_Block = cache_sim[index][k];
          int least = lruBlock.getLru();
          if(curr_Block.getLru() < least) {
            lruBlock = curr_Block;
            least = curr_Block.getLru();
            lruBlockInd = k;
          }
        }
        int y = lruBlock.getdataBlock().length;
        int z = 0;
        if(lruBlock.getDirty() == 1) {
          int placeInMem = (int)((lruBlock.getTag() << getIndex(address)) | index);
//        int placeInMem = (int)((address >> getBlockOffset(address)));
          for(int l = placeInMem; l < placeInMem + y; l++) {
            String[] tem = lruBlock.getdataBlock();
            main_mem[l] = tem[z];
            z++;
          }
        }
      }
      int x = 0;
      String[] tem = new String[block_size];
      int addMoved = (int)address >> getBlockOffset(address);
      for(int m = addMoved; m < addMoved + block_size; m++) {
        tem[x] = main_mem[m];
        x++;
      }
      lruBlock.setData(tem);
      int temp = bOff;
      String s = "";
      String[] te = lruBlock.getdataBlock();
      for(int n = 0; n < size_access; n++) {
        s = s.concat(te[temp + n]);
      }
      found = 1;
      lruBlock.setDirty(0);
      lruBlock.setValid(1);
      lruBlock.setLru(lru_count);
      lruBlock.setTag(tag);
      cache_sim[index][lruBlockInd] = lruBlock;
      System.out.println("load 0x" + String.format("%x", address) + " miss " + s);
    }
    lru_count++;
  }

  public static void main(String[] args) {
    int cachesize = Integer.parseInt(args[1]);
    int assoc = Integer.parseInt(args[2]);
    int blocksize = Integer.parseInt(args[3]);
    create_mem();
    create_cache(cachesize,assoc,blocksize);
    try {
      BufferedReader reader = new BufferedReader(new FileReader(args[0]));
      String line;
      while((line = reader.readLine()) != null) {
        String[] splited = line.split("\\s+");
        String action = splited[0];
        Long address = Long.decode(splited[1]);
        int aSize = Integer.parseInt(splited[2]);
        if(action.equals("store")) {
          String toStore = splited[3];
          cache_store(address, aSize, toStore);
        }
        else if (action.equals("load")) {
          cache_load(address, aSize);
        }
      }
    }
    catch (FileNotFoundException ex) {
      System.err.format("not found");
      System.exit(1);
    }
    catch (IOException ex) {
      System.out.println("oops");
    }
  }
}
