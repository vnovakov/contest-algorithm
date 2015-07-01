
bool is_bipartite(int &n, vector<pair<int, int> > &edges, vector<int> &color) {
    color.resize(n, -1);
    vector<vector<int> > neighbors(n, vector<int>(0));
    deque<int> q;
    
    for (int i = 0; i < edges.size(); i++) {
        neighbors[edges[i].first].push_back(edges[i].second);
        neighbors[edges[i].second].push_back(edges[i].first);
    }
    
    int find_color = 0;
    int new_color = 0;
    
    while (find_color < n) {
        color[find_color] = new_color;
        q.push_back(find_color);
     
        while (!q.empty()) {
            int v = q.front();
            q.pop_front();
            for (int i = 0; i < neighbors[v].size(); i++) {
                if (color[neighbors[v][i]] == color[v]) {
                    return false;
                }
              
                if (color[neighbors[v][i]] == -1) {
                    color[neighbors[v][i]] = 2*(color[v]/2) + (1 - color[v]%2);
                    q.push_back(neighbors[v][i]);
                }
            }
        }
      
        while (find_color < n && color[find_color] != -1) {
            find_color++;
        }
        new_color += 2;
    
    }
   
    return true;  
}
