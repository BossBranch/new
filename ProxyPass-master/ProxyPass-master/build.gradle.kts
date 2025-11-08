import com.github.jengelman.gradle.plugins.shadow.transformers.Log4j2PluginsCacheFileTransformer

description = "Proxy pass allows developers to MITM a vanilla client and server without modifying them."

plugins {
    id("java")
    id("application")
    alias(libs.plugins.shadow)
}

java {
    toolchain {
        languageVersion.set(JavaLanguageVersion.of(17))
    }
}

repositories {
    mavenLocal()
    mavenCentral()
    maven("https://repo.opencollab.dev/maven-snapshots")
    maven("https://repo.opencollab.dev/maven-releases")
}

dependencies {
    compileOnly(libs.lombok)
    annotationProcessor(libs.lombok)
    compileOnly(libs.spotbugs.annotations)
    implementation(libs.bedrock.codec)
    implementation(libs.bedrock.common)
    implementation(libs.bedrock.connection)
    implementation(libs.jackson.databind)
    implementation(libs.jackson.dataformat.yaml)
    implementation(libs.common)
    implementation(libs.jansi)
    implementation(libs.jline.reader)
}

application {
    mainClass.set("org.cloudburstmc.proxypass.ProxyPass")
}

tasks.shadowJar {
    archiveClassifier.set("")
    archiveVersion.set("")
    transform(Log4j2PluginsCacheFileTransformer())

    // Auto-copy config.yml to build/libs after building
    doLast {
        val configExample = file("config.yml.example")
        val configDest = file("build/libs/config.yml")

        // Only copy if user doesn't have config.yml yet
        if (!configDest.exists() && configExample.exists()) {
            configExample.copyTo(configDest, overwrite = false)
            println("✅ config.yml created in build/libs/ from example")
            println("📝 Edit build/libs/config.yml to configure your proxy")
        } else if (configDest.exists()) {
            println("ℹ️  config.yml already exists in build/libs/ (not overwriting)")
        } else {
            println("⚠️  Warning: config.yml.example not found!")
        }
    }
}

tasks.named<JavaExec>("run") {
    workingDir = projectDir.resolve("run")
    workingDir.mkdir()
}
