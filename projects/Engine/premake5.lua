-- Engine Premake
project "Engine"
    kind "StaticLib"
    language "C++"

    local targetDirectory = "%{sln.location}\\bin"
    local objectDirectory = "%{sln.location}\\bin-int\\"

    targetdir(targetDirectory)
    objdir(objectDirectory)

    dependson {
        "GLFW",
        "vma"
    }

    files {
        "include/**.h",
        "src/**.cpp"
    }

    includedirs {
        "include",
        "%{IncludeDir.assimp}",
        "%{IncludeDir.catch}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.phonon}",
        "%{IncludeDir.physx}",
        "%{IncludeDir.pxshared}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.stb}",
        "%{IncludeDir.tbb}",
        "%{IncludeDir.vma}",
        "%{IncludeDir.vulkan}"
    }

    libdirs {
        "%{LibDir.assimp}",
        "%{LibDir.phonon}",
        "%{LibDir.tbb}",
        "%{LibDir.vulkan}"
    }

    bindirs {
        "%{BinDir.assimp}",
        "%{BinDir.phonon}",
        "%{BinDir.tbb}",
        "%{BinDir.vulkan}"
    }

    links {
        "assimp-vc140-mt",
        "GLFW",
        "phonon",
        "PhysXTask_static_64",
		"PhysX_64",
		"PhysXCommon_64",
		"PhysXExtensions_static_64",
		"PhysXPvdSDK_static_64",
		"PhysXCooking_64",
		"PhysXCharacterKinematic_static_64",
		"SceneQuery_static_64",
		"SimulationController_static_64",
		"PhysXFoundation_64",
        "vma",
        "vulkan-1"
    }

    defines {
        "GLFW_INCLUDE_NONE"
    }

    disablewarnings {
		"4005"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
        staticruntime "Off"

        ignoredefaultlibraries {
            "LIBCMT",
            "LIBCMTD"
        }

        linkoptions {
            "/ignore:4006",
            "/ignore:4221",
            "/ignore:4099",
            "/ignore:4075"
        }

        defines {
            "PRIMAL_PLATFORM_WINDOWS"
        }

        postbuildcommands {
            "xcopy \"%{sln.location}dependencies\\assimp\\bin\\assimp-vc140-mt.dll\" \"%{sln.location}bin\" /D /Y"
        }

    filter "system:linux"
        staticruntime "Off"
    
        buildoptions {
            "-std=c++17",
            "-fPIC"
        }

        defines {
            "PRIMAL_PLATFORM_LINUX"
        }

        libdirs {
            "/usr/lib/x86_64-linux-gnu"
        }

    filter "configurations:Debug"
		postbuildcommands {
			"xcopy \"%{sln.location}dependencies\\physx\\bin\\debug\\PhysX_64.dll\" \"%{sln.location}bin\" /D /Y",
			"xcopy \"%{sln.location}dependencies\\physx\\bin\\debug\\PhysXCommon_64.dll\" \"%{sln.location}bin\" /D /Y",
			"xcopy \"%{sln.location}dependencies\\physx\\bin\\debug\\PhysXCooking_64.dll\" \"%{sln.location}bin\" /D /Y",
			"xcopy \"%{sln.location}dependencies\\physx\\bin\\debug\\PhysXDevice64.dll\" \"%{sln.location}bin\" /D /Y",
			"xcopy \"%{sln.location}dependencies\\physx\\bin\\debug\\PhysXFoundation_64.dll\" \"%{sln.location}bin\" /D /Y",
			"xcopy \"%{sln.location}dependencies\\physx\\bin\\debug\\PhysXGpu_64.dll\" \"%{sln.location}bin\" /D /Y"
		}

        defines { 
            "PRIMAL_DEBUG",
            "PRIMAL_ENABLE_ASSERTS"
        }

        libdirs {
            "%{LibDir.physx}" .. "/debug/"
        }

        bindirs {
            "%{BinDir.physx}" .. "/debug/"
        }

        staticruntime "Off"
        runtime "Debug"

        symbols "On"

        links {
            "tbb_debug",
            "tbbmalloc_debug",
            "tbbmalloc_proxy_debug"
        }

    filter "configurations:Release"
		postbuildcommands {
			"xcopy \"%{sln.location}dependencies\\physx\\bin\\release\\PhysX_64.dll\" \"%{sln.location}bin\" /D /Y",
			"xcopy \"%{sln.location}dependencies\\physx\\bin\\release\\PhysXCommon_64.dll\" \"%{sln.location}bin\" /D /Y",
			"xcopy \"%{sln.location}dependencies\\physx\\bin\\release\\PhysXCooking_64.dll\" \"%{sln.location}bin\" /D /Y",
			"xcopy \"%{sln.location}dependencies\\physx\\bin\\release\\PhysXDevice64.dll\" \"%{sln.location}bin\" /D /Y",
			"xcopy \"%{sln.location}dependencies\\physx\\bin\\release\\PhysXFoundation_64.dll\" \"%{sln.location}bin\" /D /Y",
			"xcopy \"%{sln.location}dependencies\\physx\\bin\\release\\PhysXGpu_64.dll\" \"%{sln.location}bin\" /D /Y"
		}

        defines { 
            "PRIMAL_RELEASE",
			"NDEBUG"
        }

        libdirs {
            "%{LibDir.physx}" .. "/release/"
        }

        bindirs {
            "%{BinDir.physx}" .. "/release/"
        }

        staticruntime "Off"
        runtime "Release"

        optimize "On"

        links {
            "tbb",
            "tbbmalloc",
            "tbbmalloc_proxy"
        }

    filter "configurations:Dist"
        postbuildcommands {
			"xcopy \"%{sln.location}dependencies\\physx\\bin\\release\\PhysX_64.dll\" \"%{sln.location}bin\" /D /Y",
			"xcopy \"%{sln.location}dependencies\\physx\\bin\\release\\PhysXCommon_64.dll\" \"%{sln.location}bin\" /D /Y",
			"xcopy \"%{sln.location}dependencies\\physx\\bin\\release\\PhysXCooking_64.dll\" \"%{sln.location}bin\" /D /Y",
			"xcopy \"%{sln.location}dependencies\\physx\\bin\\release\\PhysXDevice64.dll\" \"%{sln.location}bin\" /D /Y",
			"xcopy \"%{sln.location}dependencies\\physx\\bin\\release\\PhysXFoundation_64.dll\" \"%{sln.location}bin\" /D /Y",
			"xcopy \"%{sln.location}dependencies\\physx\\bin\\release\\PhysXGpu_64.dll\" \"%{sln.location}bin\" /D /Y"
		}
		
		defines {
            "PRIMAL_DIST",
			"NDEBUG"
        }

        libdirs
        {
            "%{LibDir.physx}" .. "/release/"
        }

        bindirs
        {
            "%{BinDir.physx}" .. "/release/"
        }

        staticruntime "Off"
        runtime "Release"

        optimize "On"

        links {
            "tbb",
            "tbbmalloc",
            "tbbmalloc_proxy"
        }