#include "dijkstra.h"

#include <stdio.h>
#include <stdlib.h>

static Node *_djikstra(Station **stations, int number_stations, Line **lines, int src, int dest, int time);
static Node *create_node(int current, int previous, int value, int line);
static Node *_get_minimum(Node *queue, Node *old);
static Node *_add_to_queue(Node *queue, Node *node);
static Node *_remove_from_queue(Node *queue, int current);
static Node *_get_node(Node *save, int curr);
static int _get_value(Line *line, int time);

Node *dijkstra_distance(Station **stations, int number_stations, Line **lines, int src, int dest) {
    return _djikstra(stations, number_stations, lines, src, dest, 0);
}

Node *dijkstra_time(Station **stations, int number_stations, Line **lines, int src, int dest) {
    return _djikstra(stations, number_stations, lines, src, dest, 1);
}

void destroy_nodes(Node *nodes) {
    Node *tmp = NULL;
    while (nodes) {
        tmp = nodes->next;
        free(nodes);
        nodes = tmp;
    }
}

void print_path(Node *nodes, Station **stations, Line **lines) {
    int line = -1;
    int oldline = -1;

    Station *src = NULL;
    Station *curr = NULL;

    int value = -1;

    for (; nodes; nodes = nodes->next) {
        value = 0;

        if (!src) {
            src = stations[nodes->current];
            curr = src;
            oldline = line = nodes->line;
            value = nodes->value;
        }

        int cpt = 0;
        while (oldline == line && nodes && nodes->next) {
            nodes = nodes->next;
            curr = stations[nodes->current];
            oldline = nodes->line;
            value = nodes->value;
            cpt++;
        }
        printf("%s to %s with %s :: %d --- %d s\n", src->name, curr->name, lines[line - 1]->name, value, cpt);
        src = NULL;
    }
}

static Node *_djikstra(Station **stations, int number_stations, Line **lines, int src, int dest, int time) {
    if (!stations || !lines) return NULL;

    Node *djiks_path = NULL;
    Node *queue = NULL;
    Node *save = NULL;
    Path *paths = NULL;
    int *already_treated = malloc(sizeof(int) * number_stations);
    if (!already_treated) return NULL;

    for (int i = 0; i < number_stations; i++)
        already_treated[i] = 0;

    save = _add_to_queue(save, create_node(src, -1, 0, -1));
    queue = _add_to_queue(queue, create_node(src, -1, 0, -1));
    Node *min = NULL;
    int value = 0;

    while (1) {
        min = _get_minimum(queue, min);

        if (!min || min->current == dest) break;

        already_treated[min->current] = 1;
        paths = stations[min->current]->paths;

        for (; paths; paths = paths->next) {
            value = _get_value(lines[paths->corresponding_line - 1], time);

            if (already_treated[paths->next_station] == 0) {
                queue->line = paths->corresponding_line;
                save->line = paths->corresponding_line;

                queue = _add_to_queue(queue, create_node(paths->next_station, min->current, min->value + value, paths->corresponding_line));
                save = _add_to_queue(save, create_node(paths->next_station, min->current, min->value + value, paths->corresponding_line));
            }
        }
        queue = _remove_from_queue(queue, min->current);
    }

    if (min->current == dest) {
        Node *curr = min;
        Node *new = NULL;
        while (curr) {
            new = create_node(curr->current, curr->previous, curr->value, curr->line);
            new->next = djiks_path;
            djiks_path = new;
            curr = _get_node(save, curr->previous);
        }
    }

    Node *tmp = NULL;
    while (queue) {
        tmp = queue->next;
        free(queue);
        queue = tmp;
    }

    while (save) {
        tmp = save->next;
        free(save);
        save = tmp;
    }

    free(already_treated);
    return djiks_path;
}

static Node *create_node(int current, int previous, int value, int line) {
    Node *node = malloc(sizeof(Node));
    if (!node) return NULL;

    node->current = current;
    node->previous = previous;
    node->value = value;
    node->line = line;
    node->next = NULL;
    return node;
}

static Node *_get_minimum(Node *queue, Node *old) {
    Node *min = NULL;

    for (; queue; queue = queue->next) {
        if (!min)
            min = queue;

        else if (queue->value <= min->value) {
            if (old && old->current == min->current)
                continue;
            min = queue;
        }
    }

    return min;
}

static Node *_add_to_queue(Node *queue, Node *node) {
    if (!node) return queue;

    Node *curr = queue;

    for (; curr; curr = curr->next)
        if (curr->current == node->current && node->value < curr->value) {
            curr->value = node->value;
            curr->previous = node->previous;
            curr->line = node->line;
            free(node);
            return queue;
        }

    node->next = queue;
    return node;
}

static Node *_remove_from_queue(Node *queue, int current) {
    if (!queue) return NULL;

    Node *tmp = NULL;
    if (queue->current == current) {
        tmp = queue->next;
        free(queue);
        return tmp;
    }

    tmp = queue;
    for (; tmp->next && tmp->next->current != current; tmp = tmp->next)
        ;

    Node *del = tmp->next;
    if (!del) return queue;

    tmp->next = del->next;
    free(del);
    return queue;
}

static Node *_get_node(Node *save, int curr) {
    for (; save; save = save->next) {
        if (save->current == curr)
            return save;
    }

    return NULL;
}

static int _get_value(Line *line, int time) {
    if (time == 1) return line->average_time;
    return line->average_dist;
}