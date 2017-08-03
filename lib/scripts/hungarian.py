import collections
import itertools
import sys


class LeftVertex:
    """A vertex on the left side of the graph"""


    def __init__(self, name):
        """
        Construct a left vertex with the given name, no parent, and potential 0.
        :param name: the name of the vertex
        """
        self.name = name
        self.parent = None
        self.potential = 0


    def reset(self):
        """Resets a left vertex, which amounts to making sure it has no parent."""
        self.parent = None


    @property
    def is_explored(self):
        """
        Has the vertex been explored in the current phase?  This is true if and only if the vertex has a parent.
        :return: True if the vertex has been explored
        """
        return bool(self.parent)


class RightVertex(LeftVertex):
    """
    A vertex on the right side of the graph.  Such a vertex stores all the information a left vertex stores plus
    a pointer to its matching partner on the left side (or None) and a slack value (initially 0), which is the minimum
    slack among all edges between this vertex and explored vertices on the left side.
    """


    def __init__(self, name):
        """
        Construct a right vertex with the given name, potential 0, no parent, no matching partner, and slack 0.
        :param name: the name of the vertex.
        """
        super().__init__(name)
        self.match = None
        self.slack = 0


    @property
    def is_matched(self):
        """
        Is this vertex matched?
        :return: True if the vertex is matched.
        """
        return bool(self.match)


    def reset(self):
        """Resets this vertex, which amounts to removing its parent and setting its slack to infinity."""
        super().reset()
        self.slack = sys.float_info.max
        self.potential_parent = None


class HungarianAlgorithm:
    """
    Implementation of the Hungarian algorithm wrapped in a class so we can break it into small methods that share
    the necessary state.
    """


    def __init__(self, matrix):
        """
        Constructs an instance of this algorithm from a given matrix of edge weights
        :param matrix: the edge weight matrix
        """
        n = len(matrix)
        self.left = [LeftVertex(i) for i in range(n)]
        self.right = [RightVertex(i) for i in range(n)]
        self.queue = collections.deque()
        self.matrix = matrix


    def solve(self):
        """
        Computes a minimum-weight perfect matching for this graph.
        :return: the matching in the form of a list of pairs of matched vertices
        """

        # Each iteration starts from the next vertex on the left and searches for an augmenting path starting at this
        # vertex.  It then augments the matching using this augmenting path.
        for u in self.left:
            path = self.find_augmenting_path_from(u)
            self.augment_matching(path)

        # All vertices are matched.  Construct the matching.
        return [(v.match.name, v.name) for v in self.right]


    def find_augmenting_path_from(self, u):
        """
        Computes an augmenting path from u to some vertex on the right side consisting of only tight edges, possibly
        after adjusting the vertex potentials to create more tight edges.
        :param u: the start vertex of the search
        :return: an iterator over the constructed path from the tail back to u
        """

        # Reset the queue, parents, and slack values.
        self.start_phase(u)

        # Loop forever until an augmenting path is found and we break out of the loop by returning from this method.
        while True:

            # Try to find an augmenting path by exploring tight edges.
            tail = self.explore_tight_edges()

            # If no augmenting path is found, adjust vertex potentials to create more tight edges.  In the process,
            # we may find an augmenting path.
            if not tail:
                tail = self.adjust_potentials()

            # If we found an augmenting path either while exploring tight edges or while adjusting vertex potentials,
            # return an iterator over the path.
            if tail:
                return self.path_generator(tail)


    def start_phase(self, u):
        """
        Initialize the current phase.  No vertex except u has a parent.  u is its own parent, to recognize it as
        the root, and the queue contains u.  All right vertices have infinite slack for now.
        :param u: the start vertex of the current phase
        """
        for v in itertools.chain(self.left, self.right):
            v.reset()
        u.parent = u
        self.queue.clear()
        self.queue.append(u)


    def explore_tight_edges(self):
        """
        Explore tight edges to discover so far unexplored vertices starting from vertices in the queue.
        :return: the tail of an augmenting path if such a path is found, None otherwise
        """

        # Loop while the queue isn't empty
        while self.queue:

            # Get the next vertex and explore tight edges from this vertex
            u = self.queue.pop()
            tail = self.explore_tight_edges_from(u)

            # If this produced an augmenting path, return its tail
            if tail:
                return tail

        # Exhausted the queue without finding an augmenting path.  Return None to force a potential update.
        return None


    def explore_tight_edges_from(self, u):
        """
        Explore tight edges from the given vertex
        :param u: the vertex whose incident edges are to be explored
        :return: the tail of an augmenting path if one is found.  None otherwise.
        """

        print("Vertex =", u.name)

        # Iterate over all unexplored right vertices
        for v in self.right:
            if not v.is_explored:

                # Compute the slack of the edge between u and v.
                uv_slack = self.slack(u, v)

                if uv_slack == 0:
                    # If the slack is 0, the edge is tight.  We follow it, make u the parent of v and do extra work
                    # to explore v depending on whether it is matched or not.
                    v.parent = u
                    tail = self.explore_right_vertex(v)

                    # If v is not matched, self.explore_right_vertex(v) returns v as the tail of an augmenting path
                    # and we can terminate the search.
                    if tail:
                        return tail
                else:
                    # If the slack is positive, then we cannot explore v yet, but we need to update its slack because
                    # u is an explored in-neighbour of v.
                    if uv_slack < v.slack:
                        v.slack = uv_slack
                        v.potential_parent = u

        # No unexplored, unmatched neighbour of u found that is connected to u via a tight edge.  Thus, we didn't
        # find an augmenting path.
        return None


    def adjust_potentials(self):
        """
        Adjust vertex potentials to create at least one new tight edge while ensuring we still have a valid
        potential function.
        :return: The tail of an augmenting path if we find one in the process.  None otherwise.
        """

        # Find the minimum slack of all unexplored vertices on the right
        min_slack = sys.float_info.max
        for v in self.right:
            if not v.is_explored:
                min_slack = min(min_slack, v.slack)

        # Increase the potential of every explored vertex on the left by the minimum slack
        for u in self.left:
            if u.is_explored:
                u.potential += min_slack

        # Decrease the potential or slack of every vertex on the right by the minimum slack, depending on whether
        # the vertex is explored or not.
        for v in self.right:

            if v.is_explored:
                # Explored vertices decrease their potential
                v.potential -= min_slack
            else:
                # Unexplored vertices decrease their slack
                v.slack -= min_slack

                if v.slack == 0:
                    v.parent = v.potential_parent

                    # Next we check whether being able to reach v leads us to either discover an augmenting path,
                    # whose tail we return, or to more matched vertices we can enqueue to explore more tight edges
                    # in the next iteration.
                    tail = self.explore_right_vertex(v)
                    if tail:
                        return tail

        # No augmenting path found
        return None


    def explore_right_vertex(self, v):
        """
        Explore the right vertex.  If it's unmatched, all we do is return it as the tail of an augmenting path.
        If it's matched, we make it the parent of its matching partner, enqueue the matching partner, and return
        None to indicate we didn't find an augmenting path.
        :param v: the vertex to explore
        :return: v if its unmatched, None otherwise
        """
        if v.is_matched:
            v.match.parent = v
            self.queue.append(v.match)
            return None
        else:
            return v


    def slack(self, u, v):
        """
        Computes the slack between u and v based on the current vertex potentials.
        :param u: a left vertex
        :param v: a right vertex
        :return: the slack of the edge (u, v)
        """
        return self.matrix[u.name][v.name] - u.potential - v.potential


    @staticmethod
    def path_generator(v):
        """
        Returns an iterator over the path with tail v.
        :param v: the tail of the path
        :return: an iterator over the path
        """
        while v:
            # Generate the current vertex
            print("Getting vertex", v.name)
            yield v

            # If the current vertex has itself as the parent, it is the root, and we exit the loop.  Otherwise,
            # we advance to v's parent.
            if v == v.parent:
                v = None
            else:
                v = v.parent


    @staticmethod
    def augment_matching(path):
        """
        Augments the matching using the given augmenting path.  It is important that the path is provided as an
        iterator due to some magic in how the matching is calculated that wouldn't work if path were for instance
        a list.
        :param path: an iterator over an augmenting path
        """

        print("Augmenting matching")
        for (u, v) in zip(path, path):
            u.match = v
        print("Done augmenting")


def minimum_weight_perfect_matching(matrix):
    """
    Computes a minimum-weight perfect matching using the Hungarian algorithm in O(n^3) time.

    :param matrix: the input matrix represented as a list of lists
    :return: the computed matching in the form of pairs of (0-based) row index and column index that are paired
             in the matching.
    """
    return HungarianAlgorithm(matrix).solve()

matrix = \
[[1395.85,2843.28,542.697,733.835,154.383,2738.52,2920.74,2242.93,3122.98,9.48946,181.286,2217.13,2153.35,341.969,469.323,2144.88,809.175,161.656,360.207,1605.26,4209.44,699.94,632.114,63.167,41.9209,3525.12,2020.78,815.156,863.53,888.725,144.965,1400.34,82.3422,1242.14,338.73,1343.2,1226.03,3758.22,126.01,398.587,275.968,3462.71,4024.14,2033.89,2826.34,103.48,977.503,1396.53,2278.22,1715.52],\
[634.658,98.0059,2088.43,3583.08,2462.97,1204.86,469.781,907.161,138.074,3475.45,4526.01,391.845,480.967,3345.44,1670.6,1841.22,1538.38,3541.12,1923,749.84,63.654,2499.39,3235.05,4827.12,4050.97,9.50181,305.872,1336.87,2387.24,1045.65,4160.47,730.253,3204.44,1635.2,2396.15,1957.64,2775.14,294.209,2789.69,3960.82,2808.59,196.831,18.1757,1099.53,586.692,5036.07,3246.51,1077.85,220.053,2493.69],\
[1025.56,1550.44,1248.76,112.073,429.631,733.865,2685.15,2482.71,2353.09,637.907,1623.72,1850.06,791.382,131.327,312.954,371.265,119.275,1302.23,671.246,1585.86,3030.94,1.31737,2016.14,959.893,1113.62,2270.16,1064.37,1052.07,1925.57,509.889,442.803,513.481,339.445,1941.02,104.547,93.7838,73.6881,3165.96,801.944,1916.58,1205.52,1649.52,2391.16,446.829,995.803,1384.58,2500.62,280.51,1519.47,196.734],\
[1102.13,2626.44,155.553,2412.73,597.38,3870.34,1685.19,1011.41,2221.15,610.09,304.137,1419.63,2516.57,1643.42,864.108,3602.1,1565.93,161.071,413.407,883.217,3209.02,1969.41,0.0189041,980.356,412.7,2904.65,1920.16,460.034,76.4421,1036,1365.72,1714.81,927.66,320.955,1221.18,2658.35,2874.37,2436.74,297.428,70.8727,108.203,3570.59,3586.86,2990.43,3435.69,679.283,36.1977,2127.01,1799.9,3402.46],\
[6.15564,398.932,378.14,1853.18,635.382,1327.91,351.566,279.736,357.39,1162.23,1677.24,109.626,452.883,1439.56,336.28,1492.26,521.164,1099.61,327.858,44.8581,786.685,1135.57,972.564,2008.31,1425.04,550.249,167.732,104.136,575.353,120.135,1768.93,229.884,1116.91,303.278,806.211,1148.86,1631.68,615.594,723.772,1344.33,707.936,826.669,834.468,899.386,886.93,2044.76,1050.5,532.835,133.53,1713.8],\
[423.002,1496.09,2.95194,1572.61,218.603,2366.73,1090.06,647.935,1359.06,400.411,500.581,751.875,1341.22,1011.07,275.862,2204.79,710.552,212.765,59.665,383.482,2149.66,1099.79,182.683,895.311,423.59,1800.62,951.544,78.1061,105.16,344.12,982.818,772.018,532.206,175.243,585.509,1519.34,1776.2,1669.41,119.267,312.92,60.2797,2180.25,2294.98,1693.81,2027.13,788.26,292.683,1064.41,934.992,2124.9],\
[478.204,803.603,932.306,471.058,410.992,467.796,1708.82,1630.65,1403.58,787.701,1747.75,1055.53,312.298,410.276,159.549,324.816,6.80341,1287.84,469.934,917.926,1927.8,138.986,1753.51,1334.55,1264.32,1334.38,461.284,630.691,1503.82,177.414,812.833,132.617,514.183,1359.82,171.181,112.25,281.139,2055.58,752.695,1838.25,1054.55,928.671,1448.31,201.906,517.336,1690.07,2121.55,45.4789,781.303,328.919],\
[1069.39,1233.64,1712.83,320.326,832.215,312.383,2656.35,2645.6,2154.36,1203.72,2452.56,1827.35,524.872,454.09,535.487,86.4953,175.994,1993.07,1035.75,1713.13,2654.64,123.548,2719.86,1676.22,1826.76,1914.26,898.499,1331.8,2478.95,609.643,959.171,431.456,788.892,2330.31,361.438,0.680295,64.4717,2982.18,1329.09,2715.14,1788.99,1167.19,1907.91,169.675,574.004,2209.51,3218.64,162.337,1382.23,45.3603],\
[1629.87,2711.92,1204.46,114.915,338.935,1827.55,3567.33,3060.94,3446.31,261.722,914.147,2646.78,1772.93,18.3439,515.423,1192.38,521.405,832.317,708.245,2132.3,4422.14,211.091,1635.13,290.832,544.173,3563.34,1966.98,1293.83,1809.2,949.411,37.5221,1211.63,104.996,2107.43,168.275,636.286,425.833,4308.18,561.198,1332.86,934.371,3016.64,3854.09,1342.54,2180.41,602.791,2150.49,963.847,2442.14,767.077],\
[622.783,495.927,1597.09,4392.69,2451.84,2387.88,59.6312,301.728,70.4374,3375.46,3915.36,195.427,1118.46,3847.62,1820.58,3046.95,2040.83,3010.52,1755.29,436.961,129.279,3191.91,2374.02,4731.22,3683.93,244.955,606.816,1051.35,1603.11,1197.69,4422.85,1153.37,3347.14,952.607,2755.69,2894.74,3793.24,0.430333,2513.96,3155.04,2304.53,928.218,476.709,2045.96,1507.63,4656.93,2215.46,1747.11,301.825,3677.5],\
[338.152,1.80089,1560.02,2403.34,1646.44,643.631,591.221,904.416,236.546,2492.36,3563.16,336.598,123.8,2241.34,988.232,1064.2,819.274,2715.22,1284.57,568.923,314.576,1536.16,2650.01,3622.91,3064.32,97.5093,67.3058,913.721,1959.48,539.428,2964.39,274.336,2199.25,1365.27,1499.45,1114.09,1746.53,548.658,2000.63,3195.06,2117.29,78.3942,115.368,515.139,231.751,3897.06,2774.29,480.961,112.155,1540.76],\
[671.168,1904.83,62.74,2404.97,573.305,3256.39,1057.09,544.313,1499.17,745.432,590.41,860.058,1921.02,1676.85,682.38,3149.67,1297.85,313.989,301.027,460.065,2324.16,1830.38,72.2841,1287.49,638.046,2091.88,1341.67,217.594,0.456417,715.689,1549.47,1266.58,1001.05,88.2377,1138.81,2345.74,2680.2,1666.5,338.272,266.578,147.072,2757.48,2694.04,2471.88,2745.83,1027.87,75.6634,1708.77,1190.69,3094.92],\
[102.878,366.232,624.372,2693.49,1138.14,1709.9,95.7953,108.072,142.08,1789.18,2254.8,5.85531,639.677,2200.6,744.895,2044.21,981.645,1575.52,681.269,31.5381,461.121,1799.15,1238.7,2808.17,2037.2,363.045,239.796,281.73,723.753,391.365,2586,479.672,1777.08,335.134,1395.94,1735.09,2367.72,263.636,1187.69,1755.18,1080.5,833.26,654.767,1283.9,1090.63,2775.08,1217.37,908.876,89.1637,2401.66],\
[1441.36,3033.05,419.232,1164.56,239.047,3268.11,2780.26,2035.84,3117.3,72.076,43.9331,2172.9,2455.71,647.581,606.562,2699.43,1086.12,45.171,370.72,1525.17,4244.14,1068.98,369.234,143.869,1.00552,3637.99,2183.51,763.799,618.775,1013.6,364.272,1626.79,240.879,1025.05,573.416,1798.33,1726.47,3653.01,105.804,170.682,159.736,3783.71,4223.01,2473.28,3238.68,69.2497,640.128,1729.16,2346.02,2274.69],\
[1295.95,1090.6,2370.05,745.596,1438.7,81.989,2794.09,2980.49,2122.41,1980.39,3492.46,1977.94,442.249,991.414,956.13,1.54787,431.603,2889.23,1597.22,2019.04,2438.64,454.22,3619.77,2612.39,2751.43,1724.94,912.37,1799.97,3221.97,900.335,1694.33,537.771,1449.6,2902.6,824.738,110.652,265.698,2959.27,2059.56,3717.15,2572.26,858.849,1590.42,85.0301,335.427,3252.21,4128.61,237.744,1419.87,101.013],\
[1456.47,3167.42,293.435,2135.57,544.724,4104.52,2337.65,1552.44,2880.59,420.59,93.2728,1949.37,2870.73,1403.08,928.206,3669.04,1626.96,63.2298,488.755,1306.1,3997.5,1853.19,66.6323,618.065,200.957,3577.99,2342.64,695.303,271.769,1238.13,1035.9,1976.06,738.537,647.223,1132.78,2653.64,2730.69,3201.79,246.989,0.0563354,117.656,4118.47,4283.64,3189.25,3812.25,347.391,178.732,2295.85,2308.69,3330.1],\
[744.537,84.3281,2343.64,3043.4,2409.84,688.971,891.373,1378.64,396.843,3410.6,4699.54,661.048,276.798,2969.11,1586.23,1247.5,1282.36,3721.11,1996.73,1032.65,309.556,2080.63,3640.53,4691.24,4106.35,127.273,291.73,1531.48,2806.98,1015.44,3864.34,592.606,3022.4,2058.16,2149.51,1465.18,2187.99,704.528,2865.39,4284.67,3018.63,24.6717,37.452,683.9,254.42,5049.3,3764.54,784.262,346.376,1854.92],\
[1554.25,1613.52,2320.98,363.603,1223.27,338.423,3353.46,3387.58,2729.47,1595.4,3023.61,2419.13,775.356,616.771,895.238,65.8992,407.84,2561.21,1512.73,2322.37,3211.32,246.067,3445.04,2026.71,2309.69,2383.18,1286.13,1888.05,3205.96,1000.37,1187.83,737.949,1093.08,3050.77,610.516,60.5604,63.186,3663.16,1816.15,3388.8,2372.21,1428.31,2301.72,272.964,727.343,2669.21,4022.62,358.763,1868.8,0.66442],\
[180.976,982.299,76.766,1898.68,426.845,2067.5,581.502,293.775,788.273,774.228,979.311,345.12,996.038,1345.33,329.262,2087.03,711.26,553.682,151.173,113.505,1414.87,1266.39,394.199,1459.69,864.524,1166.23,584.325,11.3934,162,244.445,1454.25,563.773,866.984,71.0207,774.313,1523.62,1921.36,1017.74,367.168,667.725,278.24,1605.77,1599.14,1471.37,1612.05,1364.08,447.242,919.258,507.139,2164.78],\
[59.021,416.158,473.966,1174.18,420.683,840.562,753.976,684.358,632.149,891.968,1590.11,348.924,254.939,903.433,136.055,886.304,182.843,1055.79,257.669,258.947,1094.74,607.472,1164.31,1623,1243.28,717.117,144.579,184.455,821.94,9.75874,1266.63,53.6843,753.208,596.653,424.935,599.564,959.851,1047.02,612.686,1424.5,724.33,719.683,930.608,480.148,594.261,1788.77,1357.74,200.917,251.674,1024.84],\
[1185.89,2019.21,1049.75,80.3278,262.28,1258.19,2932.12,2564.57,2737.77,326.015,1097.68,2080.56,1202,10.6882,301.82,769.575,241.593,898.133,546.662,1685.35,3571.01,54.1084,1617.13,510.336,680.818,2782.93,1400.25,1010.92,1659.94,610.778,157.584,766.556,121.448,1820.07,51.3438,330.755,229.916,3548.54,534.333,1428.13,898.117,2252.45,3008.86,851.412,1533.79,850.285,2097.22,554.04,1840.38,474.336],\
[324.255,60.4588,1460.24,3057.34,1844.29,1186.44,257.687,547.992,41.0746,2724.55,3595.2,155.238,378.611,2749.04,1192.07,1703.3,1170.52,2721.66,1351.15,394.899,107.193,2058.11,2434.32,3946.55,3197.59,20.1991,147.409,848.483,1708.73,672.414,3419.37,488.739,2531.63,1088.5,1869.21,1679.29,2417.42,204.771,2087.87,3073.62,2078.97,271.414,118.16,978.457,592.182,4087.74,2448.82,845.196,56.7539,2243.15],\
[2140.16,3854.58,976.734,905.631,450.495,3529.53,3933.76,3103.94,4195.01,141.553,213.299,3126.99,2994.77,508.251,918.182,2755.07,1307.46,330.159,773.856,2379.97,5443.57,1031.47,932.254,5.51139,109.468,4657.86,2887.03,1387.31,1316.97,1489.93,176.762,2107.3,251.184,1855.04,651.013,1834.2,1576.1,4912.7,384.915,555.625,566.633,4531.57,5216.14,2750.49,3734.91,36.8688,1335.8,2038.57,3206.7,2168.98],\
[112.171,74.6467,986.201,1838.1,1040.95,669.104,522.22,672.027,278.269,1732.16,2627.65,218.119,95.2362,1616.91,540.697,940.542,476.111,1909.52,750.876,315.315,517.242,1085.45,1897.21,2702.73,2202.11,244.412,0.0826032,493.388,1350.17,221.306,2183.52,93.8556,1513.24,909.026,973.397,841.839,1369.27,620.116,1316.7,2330.85,1419.77,259.133,352.019,435.63,310.325,2919.07,2040.6,289.147,58.7771,1280.46],\
[920.836,2086.81,395.36,550.31,25.455,2008.14,2311.25,1786.7,2405.04,23.5957,366.402,1648.1,1484.14,219.125,192.833,1550.01,429.815,226.644,169.22,1162.01,3341.82,414.512,656.059,223.078,154.878,2704.65,1394.17,523.353,754.938,494.169,170.02,874.352,23.4972,991.745,129.282,889.692,866.526,3018.09,74.3882,522.936,241.717,2600.57,3116.96,1404.41,2053.25,322.294,987.731,875.511,1643.76,1245.74],\
[1178.03,2306.22,697.594,300.847,108.046,1870.47,2810.64,2294.46,2808.99,73.0857,553.489,2033.49,1554.65,73.7819,279.153,1334.16,413.529,439.156,351.654,1535.07,3762.76,267.659,1033.99,197.356,271.581,3027.46,1590.67,808.169,1165.93,639.04,55.2535,966.659,3.40887,1429.66,90.038,720.331,614.347,3532.29,233.97,826.107,492.575,2727.1,3385.71,1319.58,2051.9,390.993,1447.06,857.486,1940.22,976.5],\
[701.684,266.115,2036.47,4225.69,2681.24,1813.01,260.734,658.285,68.778,3707.54,4553.8,317.133,817.913,3846.63,1912.52,2520.83,1927.92,3560.27,2028.73,666.356,1.88354,3033.65,3055.89,5124.99,4180.33,61.01,477.626,1334.33,2192.31,1237.24,4595.19,1012.57,3537.25,1433.9,2781.72,2552.19,3454.89,91.767,2897.18,3855.59,2798.98,500.963,153.696,1622.48,1033.13,5204.96,2968.54,1496.73,268.716,3215.85],\
[430.753,1381.99,154.214,841.936,25.9712,1692.72,1451.87,1056.76,1545.8,186.842,542.647,941.991,1010.48,458.699,56.6407,1436.76,306.132,268.653,11.5326,581.784,2330.36,509.22,491.586,594.705,338.266,1836.23,829.757,169.959,437.236,191.65,511.453,507.334,192.349,518.745,182.139,856.101,1002.46,2025.9,65.6246,525.497,155.059,1895.76,2225.86,1125.72,1559.67,650.204,727.499,626.035,969.838,1299.85],\
[395.395,177.501,1481.05,1450.04,1198.4,221.798,1128.42,1357.26,687.822,1899.04,3084.35,662.471,1.51064,1418.62,640.593,428.542,370.484,2354.56,1038.62,794.355,889.188,814.92,2584.68,2814.02,2517.14,482.326,122.73,898.77,2032.65,362.514,2096.87,95.9395,1539.38,1572.9,904.697,463.689,901.309,1193.45,1628.41,2943.93,1882.45,170.564,467.674,114.746,58.9786,3204.12,2850.13,119.906,335.215,738.288],\
[405.628,630.164,970.819,3820.5,1806.21,2495.41,6.1343,57.085,153.647,2552.11,2876.63,93.3571,1146.36,3198.11,1358.79,2986.87,1708.91,2121.09,1185.37,178.34,398.758,2745.05,1533.06,3727.38,2736.28,457.267,579.589,605.411,926.786,882.092,3588.52,1002.43,2615.84,452.578,2212.39,2657.72,3440.42,109.497,1770.72,2190.16,1538.16,1195.66,797.967,2026.89,1666.18,3578.14,1390.27,1591.78,282.754,3462.39],\
[749.502,208.803,2211.26,1989.83,1889.24,184.832,1399.16,1800.45,812.162,2739.68,4152.33,947.095,89.1572,2054.15,1168.6,520.748,756.329,3296.09,1687.74,1215.28,851.959,1269.51,3525.68,3796.07,3485.84,470.727,291.977,1463.83,2835.49,775.368,2904.93,348.542,2280.07,2225.61,1472.95,725.52,1244.96,1323.17,2426.05,3976.05,2724.23,59.2498,345.075,204.199,11.7073,4277.28,3798.06,347.982,522.969,954.851],\
[461.349,1442.65,146.185,2735.85,786.939,3002.15,593.491,224.381,979.736,1114.08,1053.72,493.873,1619.28,2013.01,751.659,3066.27,1320.35,648.319,403.652,221.598,1651.54,2010.38,282.327,1835.38,1067.72,1515,1016.57,170.498,65.6408,641.028,2012.76,1091.95,1334.89,2.75019,1337.07,2375.01,2842.59,1069.22,587.126,611.81,365.977,2240.83,2061.13,2288.01,2380.59,1584.3,230.808,1595.4,806.849,3159.59],\
[130.928,844.124,130.568,1284.67,219.762,1504.62,801.78,547.387,877.501,549.138,945.385,434.679,692.377,865.532,104.238,1450.87,347.428,532.03,54.5237,207.386,1501.76,760.084,564.901,1166.46,735.14,1142.46,438.379,22.3368,352.247,71.7742,1033.63,308.031,547.281,272.049,408.734,964.761,1277.36,1235.94,264.256,763.927,287.546,1340.05,1497.3,987.248,1206.34,1193.15,713.568,531.817,480.011,1483.53],\
[1738.45,2484.06,1705.82,0.0153067,629.564,1253.05,3787.87,3451.89,3452.48,668.519,1645.48,2790.53,1481.08,76.5462,654.331,678.859,444.302,1463.6,1038.04,2395.8,4288.25,96.2383,2396.47,772.592,1125.65,3376.33,1852.07,1624.59,2465.4,1025.15,283.748,1093.67,361.945,2642.27,246.316,320.58,122.485,4406.46,1014.04,2121.75,1501.17,2580.02,3518.99,929.808,1703.7,1245.62,2982.64,735.514,2423.71,329.547],\
[229.624,800.434,392.385,2915.47,1054.38,2388.88,172.202,26.3108,398.245,1588.81,1780.75,128.584,1100.28,2283.56,804.486,2648.21,1220.9,1201.2,583.316,39.0077,852.682,2044.31,779.663,2520.37,1687.98,782.276,562.723,206.053,370.962,523.539,2499.28,781.885,1701.72,102.413,1484.28,2163.81,2766.09,458.23,968.997,1253.35,775.428,1442.52,1200.87,1822.88,1708.61,2357.38,710.238,1289.78,344.103,2922.2],\
[233.093,806.607,396.896,723.7,166.487,946.392,1222.39,1025.99,1124.59,489.434,1140.22,698.591,460.461,476.718,12.5732,817.234,73.2927,728.746,130.554,490.494,1729.46,320.655,994.234,1038.83,804.328,1238.94,405.6,219.897,791.063,31.635,734.076,150.985,362.892,708.52,151.179,442.005,659.999,1639.58,347.935,1112.48,511.486,1133.63,1487.96,537.234,837.157,1222.79,1259.28,212.953,592.85,808.11],\
[627.379,565.376,1532.91,807.892,950.027,124.397,1774.72,1902.73,1288.58,1503.15,2743.43,1130.4,131.338,868.183,504.689,130.225,175.611,2134.43,965.876,1154.48,1621.28,381.06,2610.49,2213.6,2136.93,1051.89,386.006,1033.22,2198.26,389.157,1478.5,149.788,1105.83,1877.07,555.948,123.002,383.934,1954.33,1424.2,2798.9,1784.76,514.217,1029.87,12.7572,170.727,2684.04,2992.22,26.0607,734.748,279.047],\
[1040.1,631.453,2349.82,1247.24,1654.36,3.03421,2180.29,2489.62,1511.34,2351.79,3872.49,1513.07,207.083,1440.71,1041.62,117.064,531.779,3140.85,1659.65,1674.27,1682.28,765.726,3670.44,3184.09,3140.16,1107.34,587.444,1673.42,3125.95,825.986,2239.71,403.481,1828.21,2658.1,1093.51,300.699,619.285,2218.71,2264.3,3928.77,2700.42,402.241,952.703,39.5832,83.2618,3779.75,4085.96,218.282,988.035,377.211],\
[208.451,321.694,908.372,1036.5,651.407,412.157,1044.22,1095.34,748.446,1194.92,2154.59,556.124,77.2755,913.232,262.189,480.015,132.034,1557.28,541.584,546.257,1118.01,496.477,1799.25,1958.56,1685.22,677.94,122.748,495.633,1392.32,107.156,1415.19,2.66005,933.824,1089.6,476.101,342.98,690.35,1256.04,976.266,2059.18,1190.91,455.846,774.346,178.023,269.311,2260.92,2063.1,44.4392,322.934,657.55],\
[1846.84,3263.06,1031.53,425.886,323.249,2638.46,3734.11,3055.6,3807.07,118.387,475.337,2861.84,2349.97,179.883,655.957,1920.11,855.673,502.629,679.017,2221.57,4930.71,549.283,1216.34,50.813,239.979,4100.16,2396.48,1290.84,1506.78,1170.13,14.8169,1616.56,96.4806,1936.31,337.713,1173.99,928.885,4603.99,400.016,866.019,680.846,3756.69,4528.07,2001.97,2927.49,223.079,1680.88,1452.38,2799.5,1402.88],\
[783.676,2113.88,64.5685,1514.75,201.442,2860.11,1646.18,1060.64,1991.69,237.991,213.914,1237.72,1834.5,924.543,400.073,2547.49,903.969,47.4313,129.374,746.276,2929.38,1167.46,102.527,573.25,185.913,2508.12,1439.46,272.25,160.267,596.945,764.165,1135.18,419.754,372.721,610.936,1740.58,1884.93,2353.9,50.0645,116.424,0.0198191,2872.63,3069.87,2105.97,2599.16,436.522,248.277,1392.06,1458.26,2333.75],\
[1768.24,3567.6,503.586,1676.84,472.788,4047.97,3015.41,2166.88,3491.81,238.662,0.234435,2465.84,3043.72,1044.67,931.904,3450.02,1552.51,59.6155,570.879,1746.74,4701.87,1571.12,288.545,272.425,55.0803,4137.59,2651.85,953.291,598.566,1371.46,644.376,2107.25,505.153,1075.74,948.026,2424.44,2353.25,3960.82,233.634,80.6593,209.489,4453.96,4817.71,3149.87,3945.83,90.8705,508.491,2287.39,2746.03,2984.49],\
[303.285,255.673,1186.43,3413.85,1801.08,1758.91,53.2549,239.289,9.0518,2629.11,3242.1,51.3303,683.764,2953.2,1236.27,2277.89,1391.56,2415.04,1236.42,226.564,149.268,2364.76,1970.88,3843.56,2966.79,141.17,287.333,683.462,1291.07,725.312,3498.13,681.064,2558.1,729.111,2010.18,2114.97,2886.07,65.0401,1911.88,2630.3,1791.64,634.489,352.472,1430.14,1040.94,3844.19,1904.22,1156.01,91.3989,2798.99],\
[1186.45,2709.2,240.765,2989.51,882.441,4277.5,1534.72,872.774,2142.81,942.986,534.893,1376.8,2744.24,2134.23,1127.18,4096.7,1908.28,353.789,600.841,867.352,3096.49,2441.04,38.7888,1399.31,697.637,2886.34,2039.92,542.663,68.7464,1231.5,1847.72,1940.98,1313.91,271.132,1605.64,3128.99,3431.36,2256.46,523.017,189.559,253.901,3723.53,3606.21,3362.83,3714.87,1020.76,0.0414017,2453.03,1828.77,3960.87],\
[1525.43,1855.99,1976.16,134.282,893.455,608.909,3415.9,3304.08,2908.36,1135.42,2381.9,2460.17,957.397,314.812,704.182,219.976,329.03,2029.16,1226.78,2246.49,3529.01,97.825,2927.35,1440.17,1746.48,2670.83,1409.39,1682.19,2808.53,912.151,741.732,781.565,712.23,2783.25,374.677,74.3202,0.408583,3846.75,1402,2787.35,1928.21,1784.23,2679.2,440.403,1018.06,2013.14,3505.89,413.953,1984.73,44.5132],\
[2059.06,3872.55,779.24,1283.27,474.957,3909.14,3632.34,2761.13,4014.93,169.466,63.1269,2934.17,3147.2,765.83,970.367,3186.12,1487.17,179.529,708.906,2172.92,5278.03,1325.38,620.274,79.5939,47.1146,4583.17,2900.78,1238.62,999.344,1507.15,371.265,2206.69,366.258,1540.04,817.997,2187.2,1994.18,4623.99,313.662,299.062,397.79,4667.65,5215.59,3054.19,3983.46,1.2451,943.043,2250.37,3119.32,2628.18],\
[638.866,1403.29,581.571,321.233,90.2193,1122.05,2010.49,1696.48,1895.78,257.638,920.654,1325.65,818.306,140.445,62.7304,793.156,93.9015,637.149,217.386,999.568,2643.68,117.391,1121.68,602.099,565.819,2004.31,869.081,504.776,1065.29,245.104,309.472,414.55,113.705,1130.35,5.33727,352.816,400.291,2552.48,293.74,1073.12,545.002,1713.97,2264.7,688.396,1200.69,842.883,1489.13,348.983,1174.66,620.679],\
[767.481,2010.39,151.121,1005.36,56.2039,2379.16,1866.55,1315.5,2091.95,81.1877,232.727,1342.93,1586.34,536.597,234.239,2005.51,611.284,73.4185,80.5558,859.269,3022.88,750.811,298.557,360.315,117.446,2504.53,1333.11,316.11,369.56,474.049,433.552,934.179,176.4,587.181,322.01,1271.86,1343.32,2568.33,0.0286782,249.239,50.4769,2652.23,2994.03,1698.33,2256.86,334.362,529.049,1073.92,1457.49,1755.52],\
[1172.61,2706.45,216.839,1480.42,253.964,3293.5,2233.68,1532.51,2626.18,166.676,63.4813,1749.47,2301.44,883.653,568.516,2845.33,1112.29,0.0797032,268.888,1155.66,3686.6,1252.1,151.384,359.562,64.0695,3190.57,1922.39,529.81,324.799,879.76,620.441,1499.5,377.956,657.736,678.513,1946.85,1986.06,3048.49,72.5759,58.3012,44.5733,3511.04,3798.55,2481.65,3118.73,213.883,339.444,1709.6,1986.17,2513.78],\
[87.0459,115.374,883.215,2370.08,1188.13,1116.83,230.395,358.329,104.477,1905.8,2629.95,53.667,299.55,2024.74,695.429,1466.99,756.64,1892.31,788.64,154.894,335.975,1508.04,1693.77,2950.85,2290.82,171.805,56.6455,421.936,1119.48,318.42,2544.47,261.725,1772.44,658.855,1266.61,1303.69,1918.46,321.802,1369.47,2205.01,1366.58,414.732,348.298,814.736,605.292,3054.29,1745.01,583.023,1.44014,1858.04]]
import numpy as np
import test2 as t
randomList = np.random.rand(50,2,2)
print(randomList)
t.scatterPlot(randomList)
matrix=
print(minimum_weight_perfect_matching(matrix))
t.plt.show()
