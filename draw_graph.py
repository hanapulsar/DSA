from pyvis.network import Network
import os

def draw_graph():
    if not os.path.exists("graph_export.txt"):
        print("Error: graph_export.txt not found.")
        return

    # Создаем объект сети. heading - заголовок, select_menu - поиск узлов
    net = Network(height="800px", width="100%", bgcolor="#222222", font_color="white", directed=True)

    # Настройки физики (Force Atlas 2 - один из лучших алгоритмов для "распутывания")
    net.force_atlas_2based()

    with open("graph_export.txt", "r", encoding="utf-8") as f:
        mode = None
        for line in f:
            line = line.strip()
            if not line or line == "VERTICES": mode = "V"; continue
            if line == "EDGES": mode = "E"; continue
            
            if mode == "V":
                net.add_node(line, label=line, title=f"Vertex: {line}", size=25)
            elif mode == "E":
                parts = line.split(";")
                if len(parts) == 3:
                    u, v, w = parts[0], parts[1], float(parts[2])
                    # length: чем больше вес, тем длиннее "пружина" между узлами
                    # label: текст на ребре
                    # width: толщина линии
                    net.add_edge(u, v, label=str(w), value=w, length=w*20, color="#666666")

    # Включаем панель настроек прямо в браузере, чтобы можно было покрутить физику руками!
    # net.show_buttons(filter_=['physics']) 

    # Сохраняем и открываем
    output_file = "graph_map.html"
    net.save_graph(output_file)
    print(f"Interactive graph saved to {output_file}")
    
    # Пытаемся открыть в браузере автоматически
    import webbrowser
    webbrowser.open(os.path.abspath(output_file))

if __name__ == "__main__":
    draw_graph()