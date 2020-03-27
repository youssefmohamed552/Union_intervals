#include <iostream>
#include <tgmath.h>
#include <vector>


class SegmentTree{
  private:
    std::vector< std::pair<int , int> > m_arr;
    std::vector<int> taken;
    std::vector<int> match;
  public:
    SegmentTree(int n, const std::vector<int>& a ){
      // std::cout << "Segment Tree creating \n";
      int s = 1 << ((int)log2(n)+1);
      int tree_size = ((s * 2) - 1) ;
      // std::cout << "the number of nodes : " << tree_size << std::endl;
      m_arr = std::vector< std::pair<int , int> >(tree_size);
      taken = std::vector< int >(tree_size);
      match = std::vector< int >(tree_size);
      fill_array(a, 0, a.size()-1 , 0);
    }
    int parent(int index) const { return (index-1) / 2; }
    int left(int index) const { return (index * 2) + 1; }
    int right(int index) const { return (index * 2) + 2; }
    bool is_leaf(int index) const { int l = left(index); return ( l >= m_arr.size() || (m_arr[l].first == 0 && m_arr[l].second == 0)); }
    void fill_array(const std::vector< int >& a, int start, int size, int pos){
      // std::cout << "trying to fill array start : " << start << " size : " << size << " pos: "<< pos << "\n";
      // std::cout << "[";
      // for(int i = start; i <= start+size; i++){
        // std::cout << a[i] << " ";
      // }
      // std::cout << "]\n";
      if(size <= 1){
        m_arr[pos] = std::make_pair(a[start],a[start+1]);
        return;
      }
      m_arr[pos] = std::make_pair(a[start], a[start + size]);
      fill_array(a, start, size/2, left(pos));
      fill_array(a, start + (size/2), size - (size/2), right(pos));
    }

    int update(char cmd, int left, int right){
      switch(cmd){
        case 'I':
          insert(0, left, right);
          break;
        case 'D':
          del(0, left, right);
          break;
        default:
          std::cout << "I am not sure what this command is\n";
      }
      /*
      if(index == 16 || index == 15){
      for(int i = 0; i < match.size(); i++){
         std::cout << i << ":(" << match[i] << ") ";
      }
      std::cout << "\n";
      for(int i = 0; i < match.size(); i++){
        std::cout << i << ":(" << taken[i] << ") ";
      }
      std::cout << "\n";
      }
      */
      return match[0];
    }

    int insert(int root, int left, int right){
      // if(taken[root] > 0) return;
      // if the interval is conical
      if(left == m_arr[root].first && right == m_arr[root].second){
        // std::cout << "conical\n";
        match[root] = right-left;
        taken[root]++;
        return right-left;
      }
      int left_child = this->left(root);
      int right_child = this->right(root);
      // if it lies in the left
      if(right <= m_arr[left_child].second){
        // std::cout << "in the left side where overall length is (" << right-left << ")\n" ;
        int res = insert(left_child, left, right);
        if(taken[root] <= 0) match[root] = match[left_child] + match[right_child];
        // if(res == (m_arr[root].second - m_arr[root].first)) taken[root]++;
        return res;
      }
      // if it lies in the right
      if(left >= m_arr[right_child].first){
        // std::cout << "in the right side where overall length is (" << right-left << ")\n";
        int res = insert(right_child, left, right);
        if(taken[root] <= 0) match[root] = match[left_child] + match[right_child];
        // if(res == (m_arr[root].second - m_arr[root].first)) taken[root]++;
        return res;
      }
      // if it lies in both left and right 
      // std::cout << "in both\n";
      int l_res = insert(left_child, left, m_arr[left_child].second );
      int r_res = insert(right_child, m_arr[right_child].first, right);
      int res = l_res + r_res;
      if(taken[root] <= 0) match[root] = match[left_child] + match[right_child];
      // if(res == (m_arr[root].second - m_arr[root].first)) taken[root]++;
      return res;
    }

    void del(int root, int left, int right){
      int left_child = this->left(root);
      int right_child = this->right(root);
      // if the interval is the conical
      if(left == m_arr[root].first && right == m_arr[root].second){
        if(taken[root] > 0)taken[root]--;
        if(taken[root] <= 0) {
          if(!is_leaf(root)) match[root] = match[left_child] + match[right_child];
          else match[root] = 0;
        }
        return;
      }
      // if it lies in the left
      if(right <= m_arr[left_child].second){
        // std::cout << "delete from the left\n";
        // if(right != left && taken[root] > 0)taken[root]--;
        del(left_child, left, right);
        if(taken[root] <= 0)match[root] = match[left_child] + match[right_child];
        return;
      }
      // if it lies in the right
      if(left >= m_arr[right_child].first){
        // std::cout << "delete from the right\n";
        del(right_child, left, right);
        if(taken[root] <= 0)match[root] = match[left_child] + match[right_child];
        // if(right != left && taken[root] > 0)taken[root]--;
        return;
      }
      // if it lies in both
      del(left_child, left, m_arr[left_child].second);
      del(right_child, m_arr[right_child].first, right);
      if(taken[root] <= 0)match[root] = match[left_child] + match[right_child];
      // if(right != left && taken[root] > 0)taken[root]--;

    }

    void print(int root) const {
      if(root >= m_arr.size() || (m_arr[root].first == 0 && m_arr[root].second == 0)) return;
      std::cout << "(" << m_arr[root].first << "," << m_arr[root].second << ") ";
      print(left(root));
      print(right(root));
    }
};

int main(void){
  // std::cout << "This program is finding the length of the union of intervals\n";
  int m = 0, n = 0;
  std::cin >> m >> n;
  std::vector<int> arr(m);
  for(int i = 0; i < m; i++){
    std::cin >> arr[i];
  }
  SegmentTree t(m , arr);
  // t.print(0);
  // std::cout << "\n";
  for(int i = 0; i < n; i++){
    char op;
    int l = 0, r = 0;
    std::cin >> op;
    std::cin >> l >> r;
    // std::cout << "The Union is " << t.update(op, l, r) << "\n";
    int out = t.update(op, l, r);
    std::cout << out << std::endl;

  }

  return 1;
}
